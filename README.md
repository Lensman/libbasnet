libbasnet
=========


C+ Networking library for Build and Shoot community.



The core functionality in protocol abstracts the networking library managing connections, from the underlying transport.

By using a loopback, it is possible for protocol conversion, so disparate versions of the protocol can talk to each other.
ie

(version 0.?  )--- udp loopback ---><---localhost---> protcol converter <---(UDP || TCP etc)-----> server version ? 

Direct passthrough is also possible.

(version 0.75 )<---(UDP)-----> server version 0.75

This way, older clients can leverage efficiencies in the new protcol, such as reduced world update packets, and cached maps.


At the moment AoS uses UDP + ENET, but this should be agnostic so that we can use websockets, TCP, RUDP in the future without affecting older clients.

Dependancies are boost::asio 1_53_0 and ENET.


Dev branch will be a moving target so use stable if you want a branch that is always working as expected.

Completed
---------
.\relay [local port] [remote host] [remote port]

This will create a UDP relay from your local machine to the server desired. This is for testing purposes, and can be used to sniff / modify packets before they hit the NIC.


