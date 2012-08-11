#!/usr/bin/env ruby
#/*++
#
#Copyright (C) 2011-2012 The Little Beige Box, http://www.beige-box.com
#Licensed under the GNU General Public License v2
#
#File name:
#
#   convertValidationData.rb
#
#Abstract:
#
#   Easy conversion of the Siri proxy data into a simple base64
#   format for the plist
#
#--*/

require 'base64'
Data = "DATA_FROM_SIRI_SERVER_HERE"
Base64.b64encode(Data)