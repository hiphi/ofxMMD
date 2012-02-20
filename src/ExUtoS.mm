//
//  ExUtoS.c
//  MMD
//
//  Created by 藤田 宗親 on 11/08/21.
//  Copyright 2011 ANSWR inc. All rights reserved.
//

#include "ExUtoS.h"
#import <Cocoa/Cocoa.h>

ExUtoS::ExUtoS(){
	
}

const char* ExUtoS::changeStr(string str){
	
	NSAutoreleasePool* pool;
    pool = [[NSAutoreleasePool alloc]init];
	
	NSString* sjisStr = [NSString stringWithCString:str.c_str() encoding:NSShiftJISStringEncoding];
	//NSLog(@"NSString::%@\n",sjisStr);
	
	//[pool release];
	
	return [sjisStr UTF8String];
}

void ExUtoS::logStr(string str){
	NSAutoreleasePool* pool;
    pool = [[NSAutoreleasePool alloc]init];
	
	NSString* sjisStr = [NSString stringWithCString:str.c_str() encoding:NSShiftJISStringEncoding];
	NSLog(@"NSString::%@\n",sjisStr);
	
	//[pool release];
}

const char* ExUtoS::utf8ToSjis(string str){
	NSAutoreleasePool* pool;
    pool = [[NSAutoreleasePool alloc]init];
	
	NSString* sjisStr = [NSString stringWithCString:str.c_str() encoding:NSUTF8StringEncoding];
	//NSLog(@"NSString::%@\n",sjisStr);
	
	//[pool release];
	
	return [sjisStr UTF8String];
}


