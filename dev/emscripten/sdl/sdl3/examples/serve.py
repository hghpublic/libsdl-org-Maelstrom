# serve.py
# https://til.bradyjoslin.com/wasm/local-server/
# https://docs.python.org/3/library/socketserver.html
# lsof -i :8000
# sudo kill -9 <pid>
# sudo kill -9 $(ps -A | grep python | awk '{print $1}')
# OSError: [Errno 98] Address already in use
# netstat -an | grep LISTEN
# netstat -ant | grep :8000
# ss -tuln | grep 8000
# SO_REUSEADDR
# # enable address reuse
# server.setsockopt(
#     socketserver.socket.SOL_SOCKET,
#     socketserver.socket.SO_REUSEADDR,
#     1,
# )
import http.server
import socketserver

if __name__ == "__main__":
    HOST, PORT = "localhost", 8000

    handler = http.server.SimpleHTTPRequestHandler
    handler.extensions_map = {
        ".html": "text/html",
        ".wasm": "application/wasm",
        "": "application/octet-stream",
    }

    with socketserver.TCPServer((HOST, PORT), handler) as server:
        print(f"open http://{HOST}:{PORT}/index.html")
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            server.shutdown()
