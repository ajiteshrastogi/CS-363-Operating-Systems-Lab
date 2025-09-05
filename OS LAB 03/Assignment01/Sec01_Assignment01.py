from bcc import BPF

# Load the C program code
bpf_text = open("trace_open.c").read()
b = BPF(text=bpf_text)

# Attach the kprobe for 'do_sys_open' with the correct function name
b.attach_kprobe(event="do_sys_open", fn_name="trace_open")

print("Tracing open() calls... Press Ctrl-C to exit.\n")

# Print output
while True:
    try:
        print(b.trace_readline())
    except KeyboardInterrupt:
        break

