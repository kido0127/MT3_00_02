#include <Novice.h>
struct Matrix4x4
{
	float m[4][4];
};
//1.行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 matrixAdd;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			matrixAdd.m[i][k] = m1.m[i][k] + m2.m[i][k];
		}
	}
	return matrixAdd;
}
// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 matrixSubtract;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			matrixSubtract.m[i][k] = m1.m[i][k] - m2.m[i][k];
		}
	}
	return matrixSubtract;
}

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 matrixMultiply = {};
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				matrixMultiply.m[i][k] += m1.m[i][j] * m2.m[j][k];
			}
		}
	}
	return matrixMultiply;
}

//5.転換行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result;
	result.m[0][0] = m.m[0][0];
	result.m[0][1] = m.m[1][0];
	result.m[0][2] = m.m[2][0];
	result.m[0][3] = m.m[3][0];
	result.m[1][0] = m.m[0][1];
	result.m[1][1] = m.m[1][1];
	result.m[1][2] = m.m[2][1];
	result.m[1][3] = m.m[3][1];
	result.m[2][0] = m.m[0][2];
	result.m[2][1] = m.m[1][2];
	result.m[2][2] = m.m[2][2];
	result.m[2][3] = m.m[3][2];
	result.m[3][0] = m.m[0][3];
	result.m[3][1] = m.m[1][3];
	result.m[3][2] = m.m[2][3];
	result.m[3][3] = m.m[3][3];
	return result;
};
//4.逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;
	float determinant =
		m.m[0][0] * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
			- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2])
		- m.m[0][1] * (m.m[1][0] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][2]
			- m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][2])
		+ m.m[0][2] * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
			- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1])
		- m.m[0][3] * (m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][1]
			- m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[1][0] * m.m[2][2] * m.m[3][1]);

	// 行列式が 0 の場合
	if (determinant == 0.0f) {
		return result;
	};

	// 余因子行列を計算
	Matrix4x4 cofactor = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 3x3 の小行列の行列式を計算
			float minor[3][3];
			int row = 0, col = 0;
			for (int r = 0; r < 4; r++) {
				if (r != i) {
					;
					col = 0;

					for (int c = 0; c < 4; c++) {
						if (c != j) {
							minor[row][col] = m.m[r][c];
							col++;
						}
						
					}
					row++;
				}
			}
			// 小行列の行列式を計算
			float minorDeterminant =
				minor[0][0] * (minor[1][1] * minor[2][2] - minor[1][2] * minor[2][1]) -
				minor[0][1] * (minor[1][0] * minor[2][2] - minor[1][2] * minor[2][0]) +
				minor[0][2] * (minor[1][0] * minor[2][1] - minor[1][1] * minor[2][0]);

			// 余因子行列の値を設定
			cofactor.m[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minorDeterminant;
		}
	}

	// 転置 (余因子行列の転置)
	Matrix4x4 adjugate = Transpose(cofactor);

	// 逆行列を計算 (余因子行列の転置を行列式で割る)
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = adjugate.m[i][j] / determinant;
		}
	}

	return result;
}


//6.単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			result.m[i][k] = 0;
		}
	}
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	return result;
};

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	// 最初にラベルを表示
	Novice::ScreenPrintf(x, y, "%s", label);

	// 次の行から数値を表示
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Novice::ScreenPrintf(x + j * kColumnWidth, y + (i + 1) * kRowHeight, "%6.02f", matrix.m[i][j]);
		}
	}
}



const char kWindowTitle[] = "MT3_00_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Matrix4x4 m1 = {
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f
	};
	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};
	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 resultInverseM1 = Inverse(m1);
	Matrix4x4 resultInverseM2 = Inverse(m2);
	Matrix4x4 transposeM1 = Transpose(m1);
	Matrix4x4 transposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity4x4();

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, resultAdd, "Add");
		MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, resultInverseM1, "InverseM1");
		MatrixScreenPrintf(0, kRowHeight * 5 * 4, resultInverseM2, "InverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "TransposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2, "TransposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "Identity");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
