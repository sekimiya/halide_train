#include Halide

int resize_with_halide(const std::string& src_path, int dst_width, int dst_height, const std::string& dst_path)
{
    // 入力画像を読み込む。
    Halide::Runtime::Buffer<uint8_t> input = Halide::Tools::load_image(src_path);
    const int src_cols = input.width();
    const int src_rows = input.height();
    std::cout << src_cols << ", " << src_rows << std::endl;
    
    // 出力画像のバッファを用意する。
    Halide::Runtime::Buffer<uint8_t> output {dst_width, dst_height, 3};
    std::cout << output.width() << ", " << output.height() << std::endl;
    
    constexpr auto ITERATIONS {10};
    for (auto i = 0; i < ITERATIONS; ++i)
    {
        auto start {std::chrono::system_clock::now()};
        
        // ライブラリが提供する関数resizeを5つの引数を与えて呼び出す。
        resize(input, src_rows, src_cols, dst_height, dst_width, output);
        
        auto end {std::chrono::system_clock::now()};
        std::cout << boost::format("halide access[%1%]: %2% msec\n")
        % i
        % std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
 
    Halide::Tools::save(output, dst_path);
    return 0;
}

int main(){
    std::string src_path = "./hoge.png";

    
    resize_with_halide();

}