from bcc import BPF
import time

bpf_text = open("latency_read.c").read()
b = BPF(text=bpf_text)

b.attach_tracepoint(tp="syscalls:sys_enter_read", fn_name="trace_start")
b.attach_tracepoint(tp="syscalls:sys_exit_read", fn_name="trace_end")

print("Tracing read() latency... Ctrl-C to stop.")

try:
    while True:
        time.sleep(5)
        print("\n--- Read Latency Summary ---")
        for pid, total in b["avg_latency"].items():
            count = b["counts"][pid]
            avg = total.value // count.value
            max_lat = b["max_latency"][pid].value
            print(f"PID: {pid.value} | Avg Latency: {avg} us | Max Latency: {max_lat} us")
except KeyboardInterrupt:
    print("\nStopping tracing...")

