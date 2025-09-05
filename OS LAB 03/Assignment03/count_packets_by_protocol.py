from bcc import BPF
import time

# eBPF C code to count packets by protocol
bpf_code = """
#include <uapi/linux/ptrace.h>
#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>

BPF_HASH(tcp_count, u32, u64);
BPF_HASH(udp_count, u32, u64);
BPF_HASH(icmp_count, u32, u64);

int count_packets(struct __sk_buff *skb) {
    u32 key = 0;
    u64 *count;

    // Ethernet Header Pointer
    struct ethhdr *eth = bpf_hdr_pointer(skb, 0);

    // Check Ethernet Type to decide IP protocol
    if (eth->h_proto == __constant_htons(ETH_P_IP)) {
        struct iphdr *ip = (struct iphdr *)(skb->data + sizeof(struct ethhdr));

        // TCP Protocol
        if (ip->protocol == IPPROTO_TCP) {
            count = tcp_count.lookup_or_init(&key, &zero);
            (*count)++;
        }
        // UDP Protocol
        else if (ip->protocol == IPPROTO_UDP) {
            count = udp_count.lookup_or_init(&key, &zero);
            (*count)++;
        }
        // ICMP Protocol
        else if (ip->protocol == IPPROTO_ICMP) {
            count = icmp_count.lookup_or_init(&key, &zero);
            (*count)++;
        }
    }
    return 0;
}
"""

# Load the BPF program
b = BPF(text=bpf_code)

# Attach the BPF program to the network interface (eth0 in this case)
b.attach_kprobe(event="ip_rcv", fn_name="count_packets")

print("Counting packets by protocol... Press Ctrl+C to stop.")

# Monitoring the count every 5 seconds
try:
    while True:
        time.sleep(5)
        print("TCP packets: ", b["tcp_count"][0] if b["tcp_count"][0] else 0)
        print("UDP packets: ", b["udp_count"][0] if b["udp_count"][0] else 0)
        print("ICMP packets: ", b["icmp_count"][0] if b["icmp_count"][0] else 0)
except KeyboardInterrupt:
    print("Program terminated")

