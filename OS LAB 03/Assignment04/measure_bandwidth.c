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

