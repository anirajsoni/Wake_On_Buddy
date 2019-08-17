# Wake_On_Buddy
Wake-on-LAN (“WOL”) is implemented using a specially designed packet called a magic packet, which is sent to all computers in a network, among them the computer to be awakened.
Magic Packet Structure
The magic packet is a broadcast frame containing anywhere within its payload 6 bytes of all 255 (FF FF FF FF FF FF in hexadecimal), followed by sixteen repetitions of the target computer’s 48-bit MAC address, for a total of 102 bytes.
Since the magic packet is only scanned for the string above, and not actually parsed by a full protocol stack, it may be sent as any network- and transport-layer protocol, although it is typically sent as a UDP datagram to port 0, 7 or 9, or directly over Ethernet as EtherType 0x0842.
