#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script load experiment result and put it into dynamodb 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   04/25/16 - Make it work 
#   stplaydog   03/05/16 - Creation
#

from __future__ import print_function # Python 2/3 compatibility
import boto3
import json
import decimal
import sys
import time
from datetime import datetime as dt
import datetime
from time import mktime

dynamodb = boto3.resource('dynamodb', region_name='us-west-2', endpoint_url="https://dynamodb.us-west-2.amazonaws.com")

table = dynamodb.Table('OPTKIT')

res_json=sys.argv[1]

with open(res_json) as json_file:
    result         = json.load(json_file, parse_float = decimal.Decimal)

    timestr        = time.strptime(result['time'], "%Y-%m-%d.%H:%M:%S")
    timefinal      = dt.fromtimestamp(mktime(timestr))
    date_substracted = timefinal - datetime.timedelta(hours = 36)

    time           = int(time.mktime(date_substracted.timetuple()))
    application    = result['application']
    content        = result['content']

    print("Adding OPTKIT result:", time, application)

    table.put_item(
        Item={
            'time'        : time,
            'application' : application,
            'content'     : content,
        }
    )
