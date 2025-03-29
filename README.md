# Mayak

Mayak is a traceroute clone created as a Pet-poject for GL BaseCamp Linux/Networking.

## Building

```
    sudo apt install gcc build-essential make
    mkdir build
    make
```

## Running

```
    sudo ./mayak <host>
```

## Options

```
        --ipv4,         -4  # Choose IPv4
        --ipv6,         -6  # Choose IPv6
        --fqdn,         -f  # FQDN output for hop
        --max-hop,      -m  # Setup max hops
        --timeout,      -t  # Setup timeout wainting for a package
        --interface,    -i  # Choose network interface
```
