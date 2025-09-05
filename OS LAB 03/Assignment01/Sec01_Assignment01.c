#include <uapi/linux/ptrace.h>
#include <linux/sched.h>    // For TASK_COMM_LEN

int trace_open(struct pt_regs *ctx, const char __user *filename, int flags) {
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    char comm[TASK_COMM_LEN];
    bpf_get_current_comm(&comm, sizeof(comm));

    // Make filename a local char buffer to safely print it
    char filename_str[256];
    bpf_probe_read_user_str(&filename_str, sizeof(filename_str), filename);
    
    bpf_trace_printk("PID: %d | Process: %s | File: %s\n", pid, comm, filename_str);
    return 0;
}

