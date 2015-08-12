# encoding=utf-8


def app(environ, start_response):
    """A barebones WSGI application

    This is a staring point for your own web framework.
    """
    status = '200 OK'
    response_header = [('content_type', 'text/plain')]
    start_response(status, response_header)
    return ['Hello world from simple WSGI application\n']
