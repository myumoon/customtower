#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import re

# relpath
def relpath( path_, start="." ) :
    """Return a relative version of a path_"""

    if not path_ :
        raise ValueError("no path_ specified")
        
#    start_list	= os.path.abspath(start).split("/")
#    path_list	= os.path.abspath(path_).split("/")

    start_list	= start.split("/")
    path_list	= path_.split("/")
    

#    print "start_list : ", start_list
#    print "path_list  : ", path_list

    # Work out how much of the filepath is shared by start and path.
    i = len( os.path.commonprefix([start_list, path_list]) )

    rel_list = [".."] * (len(start_list)-i) + path_list[i:]
    if not rel_list:
        return "."
    return os.path.join( *rel_list )
