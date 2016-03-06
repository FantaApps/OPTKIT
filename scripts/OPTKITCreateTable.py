#
# Copy right YMSys, 2015,2016 Zhaoming Yin
#
# @brief    This script create OPTKIT experiment table in dynamodb 
#
#   MODIFIED   (MM/DD/YY)
#   stplaydog   03/05/16 - Creation
#

from __future__ import print_function # Python 2/3 compatibility
import boto3

dynamodb = boto3.resource('dynamodb', region_name='us-west-2', endpoint_url="https://dynamodb.us-west-2.amazonaws.com")


table = dynamodb.create_table(
        TableName='OPTKIT',
        KeySchema=[
            {
                'AttributeName': 'time',
                'KeyType': 'HASH'  #Partition key
            },
            {
                'AttributeName': 'application',
                'KeyType': 'RANGE'  #Sort key
            }
        ],
        AttributeDefinitions=[
            {
                'AttributeName': 'time',
                'AttributeType': 'N'
            },
            {
                'AttributeName': 'application',
                'AttributeType': 'S'
            },
        ],
        ProvisionedThroughput={
            'ReadCapacityUnits': 5,
            'WriteCapacityUnits': 5
            }
        )

print("Table status:", table.table_status)
