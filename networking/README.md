# Networking

*A bunch of notes about networking concepts*

## Table of content

- [IP Addresses](#ip-addresses)
    - [IPv4 Classes](#ipv4-classes)
    - [Special IPv4 Addresses](#special-ipv4-addresses)
    - [Subnet Mask](#subnet-mask)
    - [CIDR](#cidr)
    - [Subnetting](#subnetting)


### IP Addresses

#### IPv4 Classes

| Class | Public IP Range | Mask | Private IP Range |
| ----- | --------------- |----- | ---------------- |
| A | 1.0.0.0 - 126.255.255.255 | 255.0.0.0 | 10.0.0.0 - 10.255.255.255 |
| B | 128.0.0.0 - 191.255.255.255 | 255.255.0.0 | 172.16.0.0 to 172.31.255.255 |
| C | 192.0.0.0 - 223.255.255.255 | 255.255.255.0 | 192.168.0.0 to 192.168.255.255 |
| D | 224.0.0.0 to 239.255.255.255 | Multicast, no mask |  |
| E | 240.0.0.0 to 255.255.255.255 | Reserved, no mask |  |

<br>

#### Special IPv4 Addresses


| Class | Name | IP | Description |
| ----- | ---- | -- |  ---------- |
| A | Local Loopback Address  | 127.0.0.0 - 127.255.255.255 | Packets sent are looped through the network interface card only. Localhost. |
| A | Default Network Address  | 0.0.0.0 - 0.255.255.255 | Addresses are reserved for default network |
|  | Broadcast Address  | x.x.255.255 | Send data to all devices. Host portion has all binary ones. Disabled by default |
| E | Local Broadcast Address  | 255.255.255.255 | Send data to all devices on local network. Always dropped by routers by default |
| B | Link Local Address  | 169.254.0.0 - 169.254.255.255 | Valid only for communications within the subnetwork. Most often are assigned automatically. Allow 2 computers to communicate when DHCP servers are not available. |

<br>

#### Subnet Mask

- Used to determine network and host portion of an address
- Check if device is local or remote
- For address 10.1.1.1/16, network portion is 10.1 and host portion is 1.1.
- For address 10.1.1.1/24, network portion is 10.1.1 and host portion is 1.
- Devices 10.1.1.1 and 10.1.2.1 belong to same subnet if mask is /16. If mask is /24 then devices are on different subnet

<br>

#### CIDR

- Classless Inter-Domain Routing
- Replaces classful IP addresses
- Variable length subnet mask allows more flexibility
- Example: 10.0.0.0/20 (network is 20 bits, 12 bits is reserved for hosts)

<br>

#### Subnetting

###### Basic information

```rust
// Example 1
// Host portion of address is represented in binary

Ip         = 192.168.1.18/24
Subnet     = 192.168.1.00000000 = 192.168.1.0 
First host = 192.168.1.00000001 = 192.168.1.1 
Last host  = 192.168.1.11111110 = 192.168.1.254 
Broadcast  = 192.168.1.11111111 = 192.168.1.255 

```
```rust
// Example 2
// Network and host portion of address are split by "_"
// Host and split portion of address are represented in binary

Ip         = 172.16.35.123/20 = 172.16.0010_0011.01111011
Subnet     = 172.16.0010_0000.00000000 = 172.16.32.0
First_host = 172.16.0010_0000.00000001 = 172.16.32.1
Last_host  = 172.16.0010_1111.11111110 = 172.16.47.254 
Broadcast  = 172.16.0010_1111.11111111 = 172.16.47.255 

```
```rust
// Example 3
// Network and host portion of address are split by "_"
// Host and split portion of address are represented in binary

Ip         = 172.16.129.1/17 = 172.16.1_0000001.01111011
Subnet     = 172.16.1_0000000.00000000 = 172.16.128.0
First host = 172.16.1_0000000.00000001 = 172.16.128.1
Last host  = 172.16.1_1111111.11111110 = 172.16.255.254 
Broadcast  = 172.16.1_1111111.11111111 = 172.16.25547.255 

```
###### Subdividing subnet

- Includes "stealing" bits from host portion of an address
- Allocating "stoled" bits to network portion of a new address
- This creates multiple subnets from existing subnet
- Determine of hosts with formula: hosts <= 2^n - 2
- n is number of bits required
- Minus  2 is for broadcast (all ones) and subnet address (all zeros)
- Count host bits from right to left
- Determine number of networks with formula: networks <= 2^n
- Count network bits from left to right

```rust
// Example 1
// Given subnet 10.1.1.0/24, split it into smaller subnets each containing 14 machines

Subnet = 10.1.1.0/24 = 10.1.1.00000000
Network = 10.1.1.
Host = .0

// We need number of hosts so we use:
// hosts <= 2^n - 2  
// 14 <= 2^n - 2 => 14 <= 2^4 - 2 => 14 <= 14
// This means that 4 bits will support 14 hosts, which is what we need
// We count host bits from right to left
// Rest of the bits will belong to network portion of an address
// We only need 4 bits for hosts, remaining 4 bits that previousley belong to host
// will now belong to network portion
// We need to calculate new mask, which is 28

New subnet = 10.1.1.0000_0000/28

// We created multiple networks from existing subnet, each containing 16 addresses,
// but 2 are reserved for subnet and broadcast

First network  = 10.1.1.0000_0000 = 10.1.1.0/28 
Second network = 10.1.1.0001_0000 = 10.1.1.16/28 
Third network  = 10.1.1.0010_0000 = 10.1.1.32/28 
Fourth network = 10.1.1.0011_0000 = 10.1.1.48/28 
Last network   = 10.1.1.1111_0000 = 10.1.1.240/28 

```

```rust
// Example 2
// Given subnet 10.128.192.0/18, split it into 30 smaller subnets with as many host as possible
Subnet = 10.128.192.0/18 = 10.128.11_00000.00000000

// We need number of networks so we use:
// networks <= 2^n
// 30 <= 2^5 => 30 <= 32
// This means that we need to "steal" 5 bits from host poriton of an address and allocate it to network portion
// We count network bits from left to right and calculate new mask, which is 18 + 5 = 23

New Subnet     = 10.128.1100000_0.00000000

First network  = 10.128.1100000_0.00000000 = 10.128.192.0/23
Second network = 10.128.1100001_0.00000000 = 10.128.194.0/23
Third network  = 10.128.1100010_0.00000000 = 10.128.196.0/23
Fourth network = 10.128.1100011_0.00000000 = 10.128.198.0/23
Last network   = 10.128.1111111_0.00000000 = 10.128.254.0/23 

```
