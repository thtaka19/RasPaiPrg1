ITRON仕様に準拠したOSとしてTOPPERS/ASP3カーネルを　Raspberry Pai Zero W で動かす。オリジナルサンプルコード
=================

# 概要
日本発のリアルタイムOSであるITRON仕様に準拠したOSとしてTOPPERS/ASP3カーネルがある。
このカーネルOSのサンプルコードをRaspberry Pi Zero上で走らせる。

なお、U-Boot上にダウンロードして動作確認した。
その副作用で、読み込みができなくなったので以下の対処をした。
Raspberry Pai Zeroのベクターテーブルの開始番地宣言（単に０番地からと宣言）を追加。

個人の勉強用以外では、ソースコードを流用しないでください。

#TOPPERS/ASP3カーネルを、Raspberry Paiで動かす。には以下を参照した。
「AZOさんの　AZO crafts page　にある「Raspberry PiでTOPPERS(TRON系OS)」」

http://domisan.sakura.ne.jp/article/rp_toppers/rp_toppers.html#RPASP3



