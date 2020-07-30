from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler

import datetime

class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

with SimpleXMLRPCServer(('localhost', 8000), requestHandler=RequestHandler) as server:
    server.register_introspection_functions()

    # def adder_function(x, y):
    #     return x + y
    # server.register_function(adder_function, 'add')

    def server_hours():
        curr = datetime.datetime.now()
        return '{}:{}'.format(curr.hour, curr.minute)
    server.register_function(server_hours)

    server.serve_forever()
        
