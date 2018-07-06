//to compile
//g++ compile_static_library.cpp -g -std=c++11 -I toHalide_install_dir/Halide/include -L toHalide_install_dir/Halide/bin -lHalide -lpthread -ldl -o compile_static_library
//to excution
//LD_LIBRARY_PATH=toHalide_install_dir/Halide/bin ./compile_static_library

#include "Halide.h"
#include <stdio.h>

using namespace Halide;

int main(int argc, char const *argv[])
{
    Func brighter("brighter");
    Var x, y;

    //ループネストを表示
    //brighter.print_loop_nest();

    //画像読み込み、第一引数typr, 第二引数画像のチャネル、2:モノクロ、3:カラー
    ImageParam input(type_of<uint8_t>(), 2);

    /*
    Func::reoder
    ループネストを変更
    第一引数がinnerループ、第二引数がouterループ
    */
    //brighter.reorder(y, x);

    /*
    Func::split
    Funcのsplit関数によりVarを複数のVarに分割
    innerループのインデックスは0からsplitの(第三引数-1)
    元のループはouter * factor + innerと定義することができる
    この分割によって処理の順番が変わることはない
    */
    //brighter.split(x.__i);

    Param <uint8_t> scale;

    //brighter(x, y) = input(x * scale, y * scale);

    brighter(x, y) = input(x, y) * scale;

    brighter.vectorize(x, 16).parallel(y);

    std::vector<Argument> args = {input, scale};

    //const std::string PATH {"./"};
    
    brighter.compile_to_static_library(
        // ライブラリの保存先
        "test_lib",
        // 引数
        args,
                                        
        // 関数名はresize
        "brighter");

    //brighter.compile_to_static_library(path, args, "brighter");

    /* code */
    return 0;
}
