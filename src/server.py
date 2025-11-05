import http.server
import socketserver
import sys

# Define el puerto en el que escuchará el servidor.
# Si no se proporciona un argumento, usa el puerto 8080 por defecto.
try:
    PORT = int(sys.argv[1])
except (IndexError, ValueError):
    PORT = 8080

# Sobrescribe el método do_GET para manejar las peticiones HTTP GET.
class StatusRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
       
        # GET /status
        if self.path == '/status':
           
            # 1. Enviar la línea de estado HTTP
            self.send_response(200) 
            
            # 2. Enviar cabeceras
            self.send_header('Content-type', 'text/plain; charset=utf-8')
            self.end_headers()
            
            
            response_body = "Servicio en línea"
            self.wfile.write(response_body.encode('utf-8'))
            
            print(f"[*] Petición recibida: {self.client_address[0]}:{self.client_address[1]} -> GET {self.path}. Respuesta: 200 OK.")
        else:
            # Respuesta para cualquier otra ruta 
            self.send_error(404, "Error.")
            print(f"[*] Petición recibida: {self.client_address[0]}:{self.client_address[1]} -> GET {self.path}. Respuesta: 404 No encontrado.")

# --- Configuración y Ejecución del Servidor ---
try:
    socketserver.TCPServer.allow_reuse_address = True
    with socketserver.TCPServer(("", PORT), StatusRequestHandler) as httpd:
        print(f"Servidor HTTP escuchando en el puerto {PORT}. Presiona Ctrl+C para detenerlo.")
        httpd.serve_forever()

except KeyboardInterrupt:
    print("\n[!] Servidor detenido por el usuario (Ctrl+C).")
    httpd.server_close()

except Exception as e:
    print(f"\n[!] Error al iniciar el servidor: {e}")
