//�S.�P. �萔�̒�`
#define DATA_MAX_NUM 32

//�S.�Q. �\���̂̒�`
//���l��ێ�����e�\���̂̒�`�́A���L�̂Ƃ���B
//�S.�Q.�P. DATA_TYPE �^
typedef struct {
int data_num; // ���̓f�[�^��
float data_val[DATA_MAX_NUM]; // ���̓f�[�^�l
} DATA_TYPE;

//�S.�Q.�Q. RESULT_TYPE �^
typedef struct {
float total; // ���v�l
float average; // ���ϒl
float sigma; // �W���΍��l
} RESULT_TYPE;

