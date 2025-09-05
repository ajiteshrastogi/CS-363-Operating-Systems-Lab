from bcc import BPF
import time

# eBPF C code to count bytes per protocol
bpf_code = """
#include <uapi/linux/ptrace.h>
#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>

BPF_HASH(tcp_bytes, u32, u64);
BPF_HASH(udp_bytes, u32, u64);
BPF_HASH(icmp_bytes, u32, u64);

int count_bytes(struct __sk_buff *skb) {
    u32 key = 0;
    u64 *bytes;

    // Ethernet Header Pointer
    struct ethhdr *eth = bpf_hdr_pointer(skb, 0);

    // Check Ethernet Type to decide IP protocol
    if (eth->h_proto == __constant_htons(ETH_P_IP)) {
        struct iphdr *ip = (struct iphdr *)(skb->data + sizeof(struct ethhdr));

        // TCP Protocol
        if (ip->protocol == IPPROTO_TCP) {
            bytes = tcp_bytes.lookup_or_init(&key, &zero);
            *bytes += skb->len;
        }
        // UDP Protocol
        else if (ip->protocol == IPPROTO_UDP) {
            bytes = udp_bytes.lookup_or_init(&key, &zero);
            *bytes += skb->len;
        }
        // ICMP Protocol
        else if (ip->protocol == IPPROTO_ICMP) {
            bytes = icmp_bytes.lookup_or_init(&key, &zero);
            *bytes += skb->len;
        }
    }
    return 0;
}
"""

# Load the BPF program
b = BPF(text=bpf_code)

# Attach the BPF program to the network interface (eth0 in this case)
b.attach_kprobe(event="ip_rcv", fn_name="count_bytes")

print("Measuring bandwidth by protocol... Press Ctrl+C to stop.")

# Monitoring the bandwidth usage every 5 seconds
try:
    while True:
        time.sleep(5)
        tcp_data = b["tcp_bytes"][0] if b["tcp_bytes"][0] else 0
        udp_data = b["udp_bytes"][0] if b["udp_bytes"][0] else 0
        icmp_data = b["icmp_bytes"][0] if b["icmp_bytes"][0] else 0

        print(f"TCP Bandwidth: {tcp_data} bytes")
        print(f"UDP Bandwidth: {udp_data} bytes")
        print(f"ICMP Bandwidth: {icmp_data} bytes")
        
        # Reset the counters
        b["tcp_bytes"].clear()
        b["udp_bytes"].clear()
        b["icmp_bytes"].clear()

except KeyboardInterrupt:
    print("Program terminated")

