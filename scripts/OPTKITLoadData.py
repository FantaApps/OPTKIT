#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script load experiment result and put it into dynamodb 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   03/05/16 - Creation
#

from __future__ import print_function # Python 2/3 compatibility
import boto3
import json
import decimal

dynamodb = boto3.resource('dynamodb', region_name='us-west-2', endpoint_url="https://dynamodb.us-west-2.amazonaws.com")

table = dynamodb.Table('OPTKIT')

res_json=argv[1]

with open(res_json) as json_file:
    result         = json.load(json_file, parse_float = decimal.Decimal)

    time           = int(result['time'])
    application    = result['application']
    content        = result['']

    print("Adding OPTKIT result:", time, application)

    table.put_item(
        Item={
            'time'        : time,
            'application' : application,
            'content'     : content,
        }
    )
