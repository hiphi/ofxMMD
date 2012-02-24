ofxMMD
=====

**english below**




ofxMMDはhkrnさんのMMDAIに含まれるlibvpvlをopenframeworksに対応させたものです。
libvpvl:https://github.com/hkrn/MMDAI

# サンプル映像
→vimeo


MMDのアニメーションの再生に対応させる目的で作ったため
Boneの追加、アニメーションの編集等には対応していません。
主にPMDファイルの表示、VMDファイルの再生に対応しています。


# 使い方
bulletとassimpに依存しているため、
・ofxBullet
・ofxAssimpModelLoader
をaddonに追加し
このofxMMDもaddonに追加しておいて下さい。

そしてプロジェクトに上記三つを追加します。
※Xcodeをお使いの場合はクローン時についてくるプロジェクトファイルを使うと
 Bulletの依存ファイル等設定されているためコンパイルが通りやすいです。

コードは
(1)ofxMMDをinclude
(2)bulletの物理空間を作り引数で渡す。
(3)モデルのロード
で、モデルの表示が出来ます。

vmdファイルの読み込みにも対応しているため
PmdModelを関連づけると踊ってくれます。

詳しくはtestApp.hとtestApp.ccを読んで下さい。

モデル、モーションデータは以下よりダウンロードし、dataディレクトリに置いて下さい。
モデルデータ : http://www6.atwiki.jp/vpvpwiki/pages/65.html
モーションデータ : http://www6.atwiki.jp/vpvpwiki/pages/15.html


openframeworksのバージョンは007でテストしています。
当方の確認環境は MacOSX 10.6.8のみです。




[english]
-----

ofxMMD is load ".pmd" & ".vmd" file in OpenFrameworks.
.pmd file is MikuMikuDance file.
http://www.geocities.jp/higuchuu4/


".pmd" & ".vmd" is in vpvp wiki.
model data : http://www6.atwiki.jp/vpvpwiki/pages/65.html
motion data : http://www6.atwiki.jp/vpvpwiki/pages/15.html


# installation
Get ofxAssimpModelLoader Addon.
Get ofxBullet Addon.
Clone this addon into your openframeworks/addon folder.

Add ofxAssimpModelLoader to your project
Add ofxBullet to your project
Add ofxMMD to your project


# usage
read testApp.h and testApp.cc ...sorry.


test by OF007
my develop environment is MacOSX 10.6.8 only.
