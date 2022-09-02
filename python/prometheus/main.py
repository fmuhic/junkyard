import time
import random
from prometheus_client import start_http_server, Counter
from pprint import pprint

def process_request(counter, interval):
    counter.inc()
    time.sleep(interval)


if __name__ == '__main__':
    c = Counter('requests_total', 'Number of requests.')

    start_http_server(8000)
    while True:
        process_request(c, random.random())
