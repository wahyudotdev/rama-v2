from pythonping import ping

class ConnectionStatus(object):
    def __init__(self, host) -> None:
        self.host = host

    def latency(self):
        try:
            response = ping(self.host, count=1, size=1)
            return response.rtt_avg_ms
        except:
            pass
    
    def connected(self):
        try:
            response = ping(self.host, count=1, size=1)
            return response.success()
        except:
            pass