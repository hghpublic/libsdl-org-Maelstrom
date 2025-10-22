# serve.py
# https://til.bradyjoslin.com/wasm/local-server/
# Run python3 serve.py and open http://localhost/8000.
# http://localhost:8000/hello.html

import http.server
import socketserver

PORT = 8000

Handler = http.server.SimpleHTTPRequestHandler
Handler.extensions_map = {
    '.html': 'text/html',
    '.wasm': 'application/wasm',
    '': 'application/octet-stream',
}

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    print("open http://localhost:8000/hello.html")
    httpd.serve_forever()
