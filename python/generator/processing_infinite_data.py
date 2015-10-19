# encoding=utf-8

import time
from parsing_and_prcessing_data import nginx_log


def follow(thefile):
    ''' python version of 'tail -f'
    '''
    thefile.seek(0, 2)
    while True:
        line = thefile.readline()
        if not line:
            time.sleep(0.2)
            continue
        yield line

if __name__ == '__main__':
    logfile = open('rxgx.log')
    loglines = follow(logfile)
    log = nginx_log(loglines)
    r404 = (r for r in log if r['status'] == 404)
    for r in r404:
        print r['hosts'], r['datetime'], r['request']
