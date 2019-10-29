//４.１. 定数の定義
#define DATA_MAX_NUM 32

//４.２. 構造体の定義
//数値を保持する各構造体の定義は、下記のとおり。
//４.２.１. DATA_TYPE 型
typedef struct {
int data_num; // 入力データ数
float data_val[DATA_MAX_NUM]; // 入力データ値
} DATA_TYPE;

//４.２.２. RESULT_TYPE 型
typedef struct {
float total; // 合計値
float average; // 平均値
float sigma; // 標準偏差値
} RESULT_TYPE;

