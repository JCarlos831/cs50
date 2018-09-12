







# GET
def do_GET(self):

    # send response status code
    self.send_response(200)

    # send headers
    self.send_header("Content-type", "text/html")
    self.end_headers()

    # write message
    self.wfile.write(bytes("hello, world", "utf8"))

# Configure Server
port = 8080
server_address = ("0.0.0.0", port)
httpd = HTTPServer(server_address, HTTPServer_RequestHandler)

# Run Server
httpd.serve_forever()