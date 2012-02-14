/*
 *  ImageLoader.cpp
 *  3d_sample
 *
 *  Created by Munetika Hujita on 10/05/02.
 *  Copyright 2010 hiphi. All rights reserved.
 *
 */

#include "ImageLoader.h"
#import <Cocoa/Cocoa.h>

@interface Loader : NSObject
{
	//Test *ptr;
}
- (GLuint) load_img : (NSString*)imgPath;
@end

#define TEX_SIZE 1024 // テクスチャーのサイズ

@implementation Loader
- (GLuint) load_img : (NSString*)imgPath{
	
	NSImage* imgFile; // ファイルから読み込んだ画像
	NSImage* imgTex; // テクスチャー用に変形した画像
	NSBitmapImageRep* imgTexRep; // テクスチャーのビットマップ抽出用
	GLuint texId; // テクスチャーID
	CGFloat wid;
	CGFloat hig;
	
	// テクスチャーサイズのNSImageを作成 ( Cocoaを主に使用 )
	//NSString *_imgPath = [NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], imgPath];
	imgFile = [ [ [ NSImage alloc ] initWithContentsOfFile: imgPath ] autorelease ]; // ファイルから読み込み
	//NSLog(@"img::%@",imgFile.size());
	NSSize size = [imgFile size];
	wid = (size.width  > 0 ) ? size.width  : 2;
	hig = (size.height > 0 ) ? size.height : 2;
	//NSLog(@"size%f",size.height);
	imgTex  = [ [ [ NSImage alloc ] initWithSize : NSMakeSize( wid, hig ) ] autorelease ];
	[ imgTex lockFocus ];
	[ imgFile drawInRect : NSMakeRect( 0, 0, wid, hig )
				fromRect : NSZeroRect
			   operation : NSCompositeSourceOver
				fraction : 1.0 ]; // imgFileをimgTex内にテクスチャーサイズで描画
	[ imgTex unlockFocus ];
	imgTexRep = [ [ NSBitmapImageRep alloc ] initWithData : [ imgTex TIFFRepresentation ] ];
	glGenTextures( 1, &texId ); // 空のテクスチャーを作成
	NSLog(@"img::%@",imgFile);
	/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, [ imgTexRep bitmapData ]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);*/
	return( texId );
}
@end

ImageLoader::ImageLoader(){
	
}

GLuint ImageLoader::loadImage(string path){
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	//画像の読み込み
	id tex_1_load;
	tex_1_load = [[Loader alloc] init];
	NSString  *newString2 = [[NSString stringWithUTF8String: path.c_str()] autorelease];
	img_p = [tex_1_load load_img:newString2];
	
	return img_p;
}










