# encoding=utf-8

import requests
from requests.exceptions import RequestException
import BaseHTTPServer
from SocketServer import ThreadingMixIn


class Handler(BaseHTTPServer.BaseHTTPRequestHandler):
    def __write_response(self, ret):
        self.send_response(ret.status_code)
        for key in ret.headers:
            self.send_header(key, ret.headers[key])
        self.end_headers()
        self.wfile.write(ret.content)

    def do_GET(self):
        print self.path
        try:
            ret = requests.get(self.path, headers=self.headers)
        except RequestException, e:
            ret = e
        self.__write_response(ret)

    def do_POST(self):
        content_length = int(self.headers['content-length'])
        data = self.rfile.read(content_length)
        data = data.split('&')
        payload = {}
        for d in data:
            k, v = d.split('=')
            payload[k] = v
        print self.path, content_length, payload
        try:
            ret = requests.post(self.path, data=payload, headers=self.headers)
        except RequestException, e:
            ret = e
        self.__write_response(ret)


class ThreadHttpServer(ThreadingMixIn, BaseHTTPServer.HTTPServer):
    pass


def main():
    server = ThreadHttpServer(('', 9876), Handler)
    server.serve_forever()

if __name__ == '__main__':
    main()
