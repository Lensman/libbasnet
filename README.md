libbasnet
=========


C+ Networking library for Build and Shoot community.

Designed as a wrapper to encapsulate ENET in the hopes that it can be replaced at some point in the future.


The core functionality in protocol abstracts the networking library managing connections, from the underlying transport.
At the moment AoS uses UDP + ENET, but I this is agnostic so that we can use websockets, TCP, RUDP in the future without affecting older clients.

Dependancies are boost::asio 1_53_0 and ENET.


Dev branch will be a moving target so use stable if you want a branch that is always working as expected.

Completed
---------
.\relay [local port] [remote host] [remote port]

This will create a UDP relay from your local machine to the server desired. This is for testing purposes, and can be used to sniff / modify packets before they hit the NIC.


