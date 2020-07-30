import xmlrpc.client

server = xmlrpc.client.ServerProxy('http://localhost:8000')
print(server.server_hours())  # Returns 2**3 = 8

# Print list of available methods
print(server.system.listMethods())

