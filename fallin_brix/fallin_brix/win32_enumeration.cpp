// win32_enumeration.cpp

#include "win32_enumeration.h"

namespace
{
	sf::VideoMode s_mode;
	bool s_fullscreen;

	BOOL WINAPI DialogCallback(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static std::vector<sf::VideoMode> validModes;

		switch(msg)
		{
		case WM_INITDIALOG:
			for(unsigned int i = 0; i < sf::VideoMode::GetModesCount(); ++i)
			{
				sf::VideoMode mode(sf::VideoMode::GetMode(i));
				if(800 > mode.Width || 600 > mode.Height) continue;
				tstring desc = TEXT(" ") + boost::lexical_cast<tstring>(mode.Width) +
					TEXT("x") + boost::lexical_cast<tstring>(mode.Height) +
					TEXT(", ") + boost::lexical_cast<tstring>(mode.BitsPerPixel) + TEXT("bit");
				validModes.push_back(mode);
				ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO_MODE), desc.c_str());
			}
			ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_MODE), 0);
			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDOK:
				s_mode = validModes[ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_MODE))];
				s_fullscreen = BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_CHECK_FULLSCREEN);
				EndDialog(hDlg, TRUE);
				return TRUE;
			case IDCANCEL:
				EndDialog(hDlg, FALSE);
			default:
				return TRUE;
			};
		case WM_CLOSE:
			EndDialog(hDlg, FALSE);
			return TRUE;
		default:
			return FALSE;
		};
	}
}

bool Win32ModeEnumeration::DoEnumeration(void)
{
	int r = DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG_SETTINGS), NULL, DialogCallback);
	_mode = s_mode;
	_fullscreen = s_fullscreen;
	return 0 != r;
}