# Asynchronous UART demonstration

This example shows how to use the UART interrupt to maintain an asynchronous
buffer of incoming data from the UART. The main function dumps this buffer to
the UART console each second, independently of the UART receive interrupt
handler.
