import sys

sys.path.append("src/")

import mocores.net.protocol
import json

with open('abc.json', 'w', encoding='utf-8') as f:
    hb = mocores.net.protocol.HeartBeat()
    json.dump(hb.serialize(), f)