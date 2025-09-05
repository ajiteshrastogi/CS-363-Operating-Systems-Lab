#include <uapi/linux/ptrace.h>
#include <linux/sched.h>

BPF_HASH(start, u32, u64);
BPF_HASH(max_latency, u32, u64);
BPF_HASH(avg_latency, u32, u64);
BPF_HASH(counts, u32, u64);

int trace_start(struct pt_regs *ctx) {
    u32 pid = bpf_get_current_pid_tgid() >> 32;
    u64 ts = bpf_ktime_get_ns();
    start.update(&pid, &ts);
    return 0;
}

int trace_end(struct pt_regs *ctx) {
    u32 pid = bpf_get_current_pid_tgid() >> 32;
    u64 *tsp = start.lookup(&pid);

    if (tsp) {
        u64 delta_ns = bpf_ktime_get_ns() - *tsp;
        u64 delta_us = delta_ns / 1000; // convert to microseconds
        start.delete(&pid);

        // Update max latency
        u64 *max = max_latency.lookup(&pid);
        if (!max || delta_us > *max) {
            max_latency.update(&pid, &delta_us);
        }

        // Update average latency
        u64 *total = avg_latency.lookup(&pid);
        u64 *count = counts.lookup(&pid);
        u64 new_total = total ? *total + delta_us : delta_us;
        u64 new_count = count ? *count + 1 : 1;

        avg_latency.update(&pid, &new_total);
        counts.update(&pid, &new_count);

        bpf_trace_printk("PID: %d | Read latency: %llu us\n", pid, delta_us);
    }

    return 0;
}

