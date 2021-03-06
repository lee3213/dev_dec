// Saliencyrender_image.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"

using namespace std;

#include "define.h"
#include "global.h"

#define CREATE_BATCH 0

#include "use_json.h"
#include "set_result_path.h"

// 유일한 응용 프로그램 개체입니다.
#include "make_batch.h"

#include "saliency_main.h"
#include "dir.h"

#include "json_write.h"
#include "set_result_path.h"
#include "brush_adjust.h"
int prepare_Rendering(char * srcImgname, char * deployname);
int  read_try_scale_json_content(string path_fname);
int do_rendering();
void g_para_set() {
	g_image_divider = 15;// extern int g_image_divider;// BrushMaxSize = g_src_image_height / g_image_divider;
	int bs[MAX_DEPTH]= { 1, 1,1,1,1,1,1,1,1,1,1,1,1 };
	int ts_8[MAX_DEPTH]= { 16,8,8,8,8,8,8,8,8,1,1,1,1 };
	int ts[MAX_DEPTH]  = { 8,8,6,6,6,6,6,6,6,6,6,1,1 };
	//int ts[MAX_DEPTH] =    { 10,10,10,8,16,20,20,20,20,20,1,1 };
	int es[MAX_DEPTH] = { 20,20,20,20,20,20,1,1,1,1,1,1,1 };
	for (int i = 0; i < MAX_DEPTH; i++) {
		g_brush_scale[i] = bs[i];
		g_paint_try_scale[i] = ts[i];
		g_enhance_scale[i]=es[i];
	}
	g_BrushNumber = 48;
}
int main(int argc, char *argv[], char *envp[]) {

	int nRetCode = 0;
//	bool exists;
	string src_name, saliency_name,deploy_name;

#if CREATE_BATCH ==  1
	//string b_render_path("\\batch\\render");
	int  write_try_scale_json_content(string path_fname);
	string exe_path("C:\\render\\bin\\SaliencyPainterlyRendering.exe");
		
	string deploy_path("\\render\\deployment");
	string ts_path("\\render\\ts");
	string image_liStrk_csv_path("\\render\\list");
	string debug_path("\\render\\debug_conf");
	string batch_cfg_path("\\batch\\cfg");
	string batch_render_method_path("\\batch\\render_method_batch");
	string batch_render_para_path("\\batch\\render_para_batch");
	string batch_render_para_method_path("\\batch\\render_para_method_batch");
	string batch_render_file_path("\\batch\\render_file");
	string batch_render_file_para_path("\\batch\\render_file_para");
	string batch_render_file_method_path("\\batch\\render_file_para_method");
	string render_src_path("\\render\\src");
	
	check_and_create(ts_path, true);
	check_and_create(deploy_path, true);
	check_and_create("\\render", false);


	check_and_create(batch_cfg_path, true);
	check_and_create(batch_render_method_path, true);
	check_and_create(batch_render_para_path, true);
	check_and_create(batch_render_para_method_path, true);
	check_and_create(batch_render_file_path, true);
	check_and_create(batch_render_file_para_path, true);
	check_and_create(batch_render_file_method_path, true);
	check_and_create(debug_path, false);
	check_and_create("\\batch",true);
	
	write_try_scale_json_content(ts_path);
	nRetCode=json_write_method( deploy_path, batch_cfg_path);
	
	if (nRetCode < 0) {
		int x;
		cin >> x;
	}
	else {
		
		//string lStrk_f_para = batch_cfg_path + "\\"+string("render.cfg");
		//get_para(lStrk_f_para, para, para_cnt);
		nRetCode=make_batches(image_liStrk_csv_path,deploy_path,batch_cfg_path, batch_render_method_path,
			batch_render_para_path,
			batch_render_para_method_path,
			batch_render_file_path,
			batch_render_file_para_path,
			batch_render_file_method_path,
			render_src_path,
			exe_path);
	}
	if ( (nRetCode < 0)) {
	int x;
	
		cin >> x;
	}
#else
	g_para_set();
	
	if ( argc >2 ){
			bool exists;
			src_name = argv[1];
			cout << src_name << endl;
			exists=fileExists(src_name);
			if (exists == false) {
				cout << " NOT EXIST " << src_name << endl;
					int x;
					cin >> x;
				return -1;
			}
			deploy_name = argv[2];
			cout << deploy_name << endl;
			exists = fileExists(deploy_name);
			if (exists == false) {
				cout << " NOT EXIST " << deploy_name << endl;
				int x;
				cin >> x;
				return -2;
			}
			if (argc == 4) {
				g_debug_file = argv[3];
			}
			nRetCode=prepare_Rendering(argv[1], argv[2]);
			if ( nRetCode >= 0 )
				do_rendering();
			Mat diff_s_e;
			diff_s_e = abs(_render[RENDER_SOBEL]->result_image - _render[RENDER_ENHANCE]->result_image);
			debug_image("diff_s_e_color", diff_s_e);
			Mat diff_s_e_8UC1;
			cvtColor(diff_s_e, diff_s_e_8UC1, CV_BGR2GRAY);
			debug_image("diff_s_e_gray", diff_s_e_8UC1);
			Mat diff_s_e_inv;
			diff_s_e_inv = 255 - diff_s_e_8UC1;
			debug_image("s_e_diff_inv", diff_s_e_inv);

			Mat diff_p_e;
			int d = _render[RENDER_ENHANCE]->render_depth - 1;
			diff_p_e = abs(_render[RENDER_ENHANCE]->accu_canvas[d-1] - _render[RENDER_ENHANCE]->accu_canvas[d]);
			debug_image("diff_p_e_color", diff_p_e);
			Mat diff_p_e_8UC1;
			cvtColor(diff_p_e, diff_p_e_8UC1, CV_BGR2GRAY);
			debug_image("diff_p_e_gray", diff_p_e_8UC1);
			Mat diff_p_e_inv;
			diff_p_e_inv = 255 - diff_p_e_8UC1;
			debug_image("s_p_diff_inv", diff_p_e_inv);
		}
		
		else {
			nRetCode = -12345678;
			cout << "Error" << endl;
/*		//	cv::String f_name;
			HMODULE hModule = ::GetModuleHandle(nullptr);

			if (hModule != nullptr)
			{
				// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
				if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
				{
					// TODO: 오류 코드를 필요에 따라 수정합니다.
					wprintf(L"심각한 오류: MFC를 초기화하지 못했습니다.\n");
					nRetCode = 1;
				}
				else
				{
					// TODO: 응용 프로그램의 동작은 여기에서 코딩합니다.
					
					//sourceImage load
					//string szFilter = "All Image Files|*.BMP;*.GIF;*.JPG;*.JPEG;*.PNG;*.TIF;*.TIFF|All Files (*.*)|*.*||";
					LPCTSTR szFilter = _T( "All Image Files|*.BMP;*.GIF;*.JPG;*.JPEG;*.PNG;*.TIF;*.TIFF|All Files (*.*)|*.*||");
					CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
					fileDlg.m_ofn.lpstrTitle = _T("Load Source Image File");

					if (IDOK == fileDlg.DoModal())
					{
						CString name = fileDlg.GetPathName();
						CT2CA pszConvertedAnsiString(name);
						std::string s(pszConvertedAnsiString);
						src_name=s;
					

						}
					else

					{
						// TODO: 오류 코드를 필요에 따라 수정합니다.
						wprintf(L"심각한 오류: Get source image  실패\n");
						nRetCode = 1;
						return nRetCode;
					}
					//Saliency Image load
				
					CFileDialog fileDlg2(FALSE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
					fileDlg2.m_ofn.lpstrTitle = _T("Load Saliency Image File");

					if (IDOK == fileDlg2.DoModal())
						{
							CString name = fileDlg2.GetPathName();
							CT2CA pszConvertedAnsiString(name);
							std::string s(pszConvertedAnsiString);
							cv::String deploy_name(s);
						//	saliImg = cv::imread(f_name, CV_LOAD_IMAGE_GRAYSCALE);
						//	resize(srcImg, srcImg, cv::Size(saliImg.size().width, saliImg.size().height));
						//	//Brush initialization
						//	g_brush_set.resize(g_BrushNumber);
						//	BrushInitialization(g_brush_set);

							//Rendering
						
							 nRetCode=RenderingImage((char*)src_name.c_str(), (char*)deploy_name.c_str());
						//	imwrite("/rst/rstImg.ppm", rstImg);
					}
					else
					{
							// TODO: 오류 코드를 필요에 따라 수정합니다.
							wprintf(L"심각한 오류: get saliency file  실패\n");
							nRetCode = 1;
							return nRetCode;
					}
				}
				
			}//afx MFC
			else
			{
				// TODO: 오류 코드를 필요에 따라 수정합니다.
				wprintf(L"심각한 오류: GetModuleHandle 실패\n");
				nRetCode = 1;
			}//win init
			*/
		} // argc
#endif
    return nRetCode;
}
