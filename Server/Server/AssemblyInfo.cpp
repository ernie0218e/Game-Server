#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

//
// �M����һ���YӍ�������еČ��Լ����ơ�
// ׃���@Щ���Ե�ֵ�����޸ĽM�������P
// �YӍ��
//
[assembly:AssemblyTitleAttribute("Server")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("Server")];
[assembly:AssemblyCopyrightAttribute("Copyright (c)  2014")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

//
// �M���İ汾�YӍ�����������ֵ����:
//
//      ��Ҫ�汾
//      ��Ҫ�汾
//      �M����̖
//      ��ӆ��̖
//
// ������ָ�����е�ֵ��Ҳ�����������µķ�ʽ��ʹ�� '*' ����ӆ�ͽM����̖
// ָ�����A�Oֵ:

[assembly:AssemblyVersionAttribute("1.0.*")];

[assembly:ComVisible(false)];

[assembly:CLSCompliantAttribute(true)];

[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];
