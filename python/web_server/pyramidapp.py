# encoding=utf-8

from pyramid.config import Configurator
from pyramid.response import Response


def hello_word(request):
    return Response(
        'Hello word from Pyramid!\n',
        content_type='text/plain',
    )

config = Configurator()
config.add_route('hello', '/hello')
config.add_view(hello_word, route_name='hello')
app = config.make_wsgi_app()
