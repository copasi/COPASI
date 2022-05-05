#!/usr/bin/env python3

# BEGIN: Copyright 
# Copyright (C) 2020 Rector and Visitors of the University of Virginia 
# All rights reserved 
# END: Copyright 

# BEGIN: License 
# Licensed under the Apache License, Version 2.0 (the "License"); 
# you may not use this file except in compliance with the License. 
# You may obtain a copy of the License at 
#   http://www.apache.org/licenses/LICENSE-2.0 
# END: License 

from collections import OrderedDict
from pathlib import Path
import json
from sqlalchemy import true
import xmltodict
import requests

def createDataType(namespace):
  datatype = OrderedDict()

  datatype['@id']= namespace['mirId']
  datatype['@pattern']= namespace['pattern']

  if namespace['namespaceEmbeddedInLui']:
    datatype['@namespaceEmbeddedInPattern'] = True

  datatype['name'] = namespace['name']
  datatype['definition'] = namespace['description']
  datatype['namespace'] = namespace['prefix']

  uri = OrderedDict()
  uri['@type'] = 'URN'
  uri['#text'] = 'urn:miriam:' + namespace['prefix']

  uris = OrderedDict()
  uris['uri'] = [uri]

  datatype['uris'] = uris

  return datatype


def main():
  identifiersURL = 'https://registry.api.identifiers.org/resolutionApi/getResolverDataset'
  identifiers = json.loads(requests.get(identifiersURL).content)

  miriamURL = 'https://copasi.org/static/miriam.xml'
  response = requests.get(miriamURL)
  miriam = xmltodict.parse(response.content)
  
  for namespace in identifiers['payload']['namespaces']:
    mirId = namespace['mirId']

    found = None
    for datatype in miriam['miriam']['datatype']:
      if datatype['@id'] == mirId:
        found = datatype
        break

    if found:
      if namespace['namespaceEmbeddedInLui']:
        datatype['@namespaceEmbeddedInPattern'] = True
    else:
      datatype = createDataType(namespace)
      miriam['miriam']['datatype'].append(datatype)
      
  miriamXml = xmltodict.unparse(miriam, pretty=True, indent='  ')

  outputFile = Path('miriam.xml')
  outputFileHandle = outputFile.open('w')
  outputFileHandle.write(miriamXml)

if __name__ == "__main__":
  main()
