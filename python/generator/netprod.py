# encoding=utf-8

from extending_the_pipeline import sendto
from parsing_and_prcessing_data import nginx_log
from processing_infinite_data import follow

lines = follow(open('rxgx.log'))
log = nginx_log(lines)
sendto(log, ('', 15000))
