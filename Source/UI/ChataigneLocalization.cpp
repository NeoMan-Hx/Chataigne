#include "JuceHeader.h"
#include "ChataigneLocalization.h"

const juce::String ChataigneLocalization::englishLanguageId = "en";
const juce::String ChataigneLocalization::simplifiedChineseLanguageId = "zh_CN";
const juce::String ChataigneLocalization::bilingualChineseLanguageId = "zh_CN_bilingual";

namespace
{
juce::String activeLanguageId = ChataigneLocalization::englishLanguageId;

struct TranslationPair
{
	const char* source;
	const char* target;
};

// Keep the source strings in English so that adding a language never changes
// the names used by Chataigne's project, OSC, and scripting layers.
constexpr TranslationPair simplifiedChineseTranslations[] =
{
	{ "File", "文件" }, { "Edit", "编辑" }, { "Timeline", "时间线" },
	{ "View", "视图" }, { "Guides", "指南" }, { "Help", "帮助" },
	{ "Modules", "模块" }, { "Custom Variables", "自定义变量" },
	{ "State Machine", "状态机" }, { "States", "状态" },
	{ "Dashboard", "仪表板" }, { "Module Router", "模块路由" },
	{ "Morpher", "变形器" }, { "Sequences", "序列" },
	{ "Sequence Editor", "序列编辑器" }, { "Inspector", "检查器" },
	{ "Logger", "日志" }, { "Warnings", "警告" }, { "Outliner", "大纲" },
	{ "Parrots", "回放器" }, { "Parrot", "回放器" },
	{ "The Detective", "侦测器" }, { "Command Templates", "命令模板" },
	{ "Time", "时间" }, { "Source", "来源" }, { "Content", "内容" },
	{ "Clear", "清除" }, { "Copy All", "全部复制" },
	{ "Auto Scroll", "自动滚动" },

	{ "New", "新建" }, { "Open...", "打开…" },
	{ "Open Last Document", "打开上次文档" }, { "Save", "保存" },
	{ "Save As...", "另存为…" }, { "Save Copy", "保存副本" },
	{ "Open recent file", "打开最近文件" },
	{ "Project Settings...", "项目设置…" }, { "Preferences", "偏好设置" },
	{ "Clear Preferences", "清除偏好设置" }, { "Check for updates", "检查更新" },
	{ "Quit", "退出" }, { "Undo", "撤销" }, { "Redo", "重做" },
	{ "Copy", "复制" }, { "Cut", "剪切" }, { "Paste", "粘贴" },
	{ "Duplicate", "创建副本" }, { "Delete", "删除" },
	{ "Select all", "全选" }, { "Select Previous Item", "选择上一个项目" },
	{ "Select Next Item", "选择下一个项目" },
	{ "Move to previous", "移到上一个" }, { "Move to next", "移到下一个" },
	{ "Toggle Fullscreen", "切换全屏" },
	{ "Toggle Dashboard Edit Mode", "切换仪表板编辑模式" },
	{ "Update Dashboard Files", "更新仪表板文件" },
	{ "About...", "关于…" }, { "About", "关于" }, { "Welcome", "欢迎" },
	{ "Show Welcome Screen...", "显示欢迎界面…" }, { "Exit", "退出" },
	{ "Go to website", "打开网站" }, { "Go to Discord", "打开 Discord" },
	{ "Go to the Amazing Documentation", "打开帮助文档" },
	{ "See the changelog", "查看更新日志" },
	{ "Post an issue on github", "提交 GitHub 问题" },
	{ "Community Modules Manager", "社区模块管理器" },
	{ "Reload Custom Modules", "重新加载自定义模块" },
	{ "Exit current guide", "退出当前指南" },
	{ "Export Selection", "导出所选内容" }, { "Import...", "导入…" },

	{ "Layout", "布局" }, { "Save Current layout", "保存当前布局" },
	{ "Load Default Layout", "加载默认布局" }, { "Load Layout...", "加载布局…" },
	{ "Lock Panels", "锁定面板" }, { "Add & Link to Custom Variable...", "添加并链接到自定义变量…" },
	{ "Add & Link to Sequence...", "添加并链接到序列…" },
	{ "Create new Mapping", "创建新映射" },

	{ "Read Only", "只读" }, { "Enabled", "启用" },
	{ "Copy OSC Control Address", "复制 OSC 控制地址" },
	{ "Copy Script Control Address", "复制脚本控制地址" },
	{ "Copy Enable OSC Control Address", "复制启用状态 OSC 地址" },
	{ "Watch this with The Detective", "使用侦测器监视" },
	{ "Create new Parrot", "新建回放器" }, { "Set in Parrot", "设置到回放器" },
	{ "Create new Dashboard", "新建仪表板" }, { "Send to Dashboard", "发送到仪表板" },
	{ "Reset value", "重置值" }, { "Show Edit Window", "显示编辑窗口" },
	{ "Copy Value", "复制值" }, { "Paste Value", "粘贴值" },
	{ "Set Options...", "设置选项…" }, { "Set the range", "设置范围" },
	{ "Set a new range for this parameter", "为此参数设置新范围" },
	{ "OK", "确定" }, { "Cancel", "取消" }, { "Custom", "自定义" },
	{ "Clear Range", "清除范围" }, { "Always Notify changes", "始终通知更改" },
	{ "Manual", "手动" }, { "Expression", "表达式" }, { "Reference", "引用" },
	{ "Animation", "动画" }, { "Minimum", "最小值" }, { "Maximum", "最大值" },
	{ "Value", "值" }, { "Key", "键" }, { "Target destroyed", "目标已销毁" },

	{ "Global Settings", "全局设置" }, { "Startup and Update", "启动和更新" },
	{ "Interface", "界面" }, { "Save and Load", "保存和加载" },
	{ "Editing", "编辑" }, { "Launch Arguments", "启动参数" },
	{ "Other Settings", "其他设置" }, { "Interface Language", "界面语言" },
	{ "English", "英语" }, { "Chinese (Simplified)", "简体中文" },
	{ "Help language", "帮助语言" }, { "Font family", "字体" },
	{ "Interface scale", "界面缩放" },
	{ "Font size", "字号" }, { "Font weight", "字重" },
	{ "Regular", "常规" }, { "Medium", "中等" }, { "Semibold", "半粗" },
	{ "Bold", "粗体" }, { "Heavy", "特粗" }, { "Light", "细体" },
	{ "Thin", "纤细" }, { "Ultralight", "超细" },
	{ "Reload font renderer", "重新加载字体渲染器" },
	{ "Enable Tooltips", "启用工具提示" }, { "Use OpenGL Renderer", "使用 OpenGL 渲染器" },
	{ "UI Refresh Rate", "界面刷新率" }, { "Logger Refresh Rate", "日志刷新率" },
	{ "Always on top", "窗口置顶" }, { "System default", "系统默认" },
	{ "Enable auto-save", "启用自动保存" }, { "Auto-save current file", "自动保存当前文件" },
	{ "Auto-save on change only", "仅在更改后自动保存" },
	{ "Ask to restore on startup", "启动时询问是否恢复" },
	{ "Auto-save count", "自动保存数量" }, { "Auto-save time", "自动保存间隔" },
	{ "Compress file", "压缩文件" }, { "Log auto-save", "记录自动保存日志" },
	{ "Action On Crash", "崩溃时操作" }, { "Report", "报告" }, { "Kill", "终止" },
	{ "Reopen", "重新打开" }, { "Recover", "恢复" },
	{ "Auto send crash log", "自动发送崩溃日志" }, { "Crash Contact Mail", "崩溃联系邮箱" },
	{ "Save logs", "保存日志" }, { "Ask before removing items", "删除项目之前询问" },
	{ "Default Easing", "默认缓动" },

	{ "Module Parameters", "模块参数" }, { "Default Behaviors", "默认行为" },
	{ "Log Incoming", "记录输入" }, { "Log Outgoing", "记录输出" },
	{ "Is Connected", "已连接" }, { "Connected", "已连接" },
	{ "Connected Clients", "已连接客户端" }, { "Use Secure Connection", "使用安全连接" },
	{ "Server", "服务器" }, { "Server Name", "服务器名称" }, { "Server Path", "服务器路径" },
	{ "Local Port", "本地端口" }, { "Remote Port", "远程端口" }, { "Port", "端口" },
	{ "Address", "地址" }, { "Host", "主机" }, { "IP Address", "IP 地址" },
	{ "Network Interface", "网络接口" }, { "Value", "值" }, { "Target", "目标" },
	{ "Position", "位置" }, { "Color", "颜色" }, { "Type", "类型" },
	{ "Name", "名称" }, { "Description", "描述" }, { "Enabled", "启用" },
	{ "Mode", "模式" }, { "Control Mode", "控制模式" }, { "Control Address", "控制地址" },
	{ "Script Control Address", "脚本控制地址" }, { "OSC Control Address", "OSC 控制地址" },
	{ "Auto Trigger", "自动触发" }, { "Auto Start", "自动开始" }, { "Auto Stop", "自动停止" },
	{ "Auto Next On Finish", "结束后自动下一个" }, { "Loop", "循环" },
	{ "Always Update", "始终更新" }, { "Send On Play", "播放时发送" },
	{ "Send On Stop", "停止时发送" }, { "Send On Seek", "跳转时发送" },
	{ "Current Cue", "当前提示" }, { "Next Cue", "下一个提示" },
	{ "Next cue", "下一个提示" },
	{ "Current Cue Name", "当前提示名称" }, { "Next Cue Name", "下一个提示名称" },
	{ "Current Color", "当前颜色" }, { "Next Color", "下一个颜色" },
	{ "Current Text Color", "当前文字颜色" }, { "Next Text Color", "下一个文字颜色" },
	{ "Start Channel", "起始通道" }, { "End Channel", "结束通道" },
	{ "Channel", "通道" }, { "Universe", "宇宙" }, { "Byte Order", "字节序" },
	{ "Send Mode", "发送模式" }, { "Loopback Enabled", "启用回环" },
	{ "Num Slots", "插槽数量" }, { "Slot", "插槽" }, { "Arm", "录制" },
	{ "Auto Disarm", "自动停止录制" }, { "Background Path", "背景路径" },
	{ "Background Scale", "背景缩放" }, { "Background Opacity", "背景不透明度" },
	{ "Show Debug", "显示调试信息" }, { "Safe Zone", "安全区域" },
	{ "Use Attraction", "使用吸引力" }, { "Attraction Mode", "吸引力模式" },
	{ "Attraction Speed", "吸引力速度" }, { "Attraction Decay", "吸引力衰减" },
	{ "Weight", "权重" }, { "Interpolation Progress", "插值进度" },
	{ "Default Load Time", "默认加载时间" }, { "Snap Keys to Frames", "关键帧吸附到帧" },
	{ "MTC Framerate", "MTC 帧率" }, { "LTC Mode", "LTC 模式" },
	{ "Send FPS", "发送帧率" }, { "Sync Offset", "同步偏移" },
	{ "Reverse Offset", "反向偏移" }, { "Reset on MTC Stop", "MTC 停止时重置" },

	{ "Loading File...", "正在加载文件…" }, { "clients", "客户端" }, { "client", "客户端" },
	{ "sponsorship", "赞助" }, { "donation", "捐赠" }, { "Nothing to paste", "没有可粘贴的内容" },
	{ "Nothing to delete", "没有可删除的项目" }, { "Nothing to duplicate", "没有可复制的项目" },
	{ "Exit", "退出" }, { "Select", "选择" }, { "[No content]", "[无内容]" },
	{ "Set Range...", "设置范围…" }, { "Control Mode", "控制模式" },
	{ "Paste (add)", "粘贴（添加）" }, { "Paste (replace)", "粘贴（替换）" },
	{ "Add...", "添加…" }, { "Add item", "添加项目" }, { "Add Item", "添加项目" },
	{ "Toggle childrens", "切换子项目" }, { "Toggle children", "切换子项目" },
	{ "Copy this line (Content only)", "复制此行（仅内容）" },
	{ "Copy this line (All)", "复制此行（全部）" },
	{ "Export Enveloppe to new mapping layer", "将包络导出到新的映射层" },
	{ "Export Enveloppe to clipboard", "将包络导出到剪贴板" },
	{ "Export Enveloppe to clipboard (data only)", "将包络导出到剪贴板（仅数据）" },
	{ "Export baked values to clipboard", "将烘焙值导出到剪贴板" },
	{ "Export baked values to clipboard (data only)", "将烘焙值导出到剪贴板（仅数据）" },
	{ "Copy filters", "复制滤镜" }, { "Paste filters", "粘贴滤镜" },
	{ "Copy outputs", "复制输出" }, { "Paste outputs", "粘贴输出" },
	{ "Copy inputs", "复制输入" }, { "Paste inputs", "粘贴输入" },
	{ "Force Relative Path", "强制相对路径" }, { "Force Absolute Path", "强制绝对路径" },
	{ "Show in Explorer", "在访达中显示" }, { "Hex Mode", "十六进制模式" },
	{ "Stretch Mode", "拉伸模式" }, { "Invert X", "反转 X" }, { "Invert Y", "反转 Y" },
	{ "Interpolation", "插值" }, { "Linear", "线性" }, { "None", "无" },
	{ "Opaque", "不透明" }, { "Not connected", "未连接" },
	{ "Don't use input", "不使用输入" }, { "Don't use output", "不使用输出" },
	{ "No service found", "未找到服务" }, { "Remove", "移除" },
	{ "Get more modules...", "获取更多模块…" }, { "Generic", "通用" },
	{ "Script callback", "脚本回调" }, { "Select an element", "选择一个元素" },
	{ "Add State", "添加状态" }, { "Add Comment", "添加注释" },
	{ "Create Transition", "创建过渡" }, { "Create Transition from here", "从此处创建过渡" },
	{ "Snapping", "吸附" }, { "Hide Tools", "隐藏工具" }, { "Show Tools", "显示工具" },
	{ "Maximize", "最大化" }, { "Minimize", "最小化" },
	{ "Create new Dashboard", "新建仪表板" }, { "Send All Variables to Dashboard", "将所有变量发送到仪表板" },
	{ "Add Group", "添加组" }, { "Add Shared Texture", "添加共享纹理" },
	{ "Add Dashboard Link", "添加仪表板链接" }, { "Add IFrame", "添加 IFrame" },
	{ "Add Input", "添加输入" }, { "Add Output", "添加输出" },
	{ "Action Input", "动作输入" }, { "Mapping Input", "映射输入" },
	{ "Action Consequence", "动作结果" }, { "Mapping Output", "映射输出" },
	{ "Input", "输入" }, { "Output", "输出" }, { "Consequence TRUE", "结果 真" },
	{ "Consequence FALSE", "结果 假" }, { "Copy conditions", "复制条件" },
	{ "Paste conditions", "粘贴条件" }, { "Copy consequences TRUE", "复制真结果" },
	{ "Paste consequences TRUE", "粘贴真结果" }, { "Copy consequences FALSE", "复制假结果" },
	{ "Paste consequences FALSE", "粘贴假结果" }, { "Remove connection", "移除连接" },
	{ "Unlink", "取消链接" }, { "From Expression", "来自表达式" },
	{ "From First Element", "来自第一个元素" }, { "From Input Values", "来自输入值" },
	{ "From Container", "来自容器" }, { "Container Mode", "容器模式" },
	{ "Change all easings", "更改所有缓动" }, { "Default Easing", "默认缓动" },
	{ "Add Int Argument", "添加整数参数" }, { "Add Float Argument", "添加浮点参数" },
	{ "Add String Argument", "添加字符串参数" }, { "Add Boolean Argument", "添加布尔参数" },
	{ "Add Color Argument", "添加颜色参数" }, { "Add Point2D Argument", "添加二维点参数" },
	{ "Add Point3D Argument", "添加三维点参数" }, { "Add Note", "添加音符" },
	{ "Add Control Change", "添加控制变化" }, { "Add Pitch Wheel", "添加弯音轮" },
	{ "Add Channel Pressure", "添加通道压力" }, { "Add After Touch", "添加触后" },
	{ "Add Program Change", "添加程序变化" }, { "Export Selection", "导出所选内容" },
	{ "Copy Style", "复制样式" }, { "Paste Style", "粘贴样式" },
	{ "Add Dashboard", "添加仪表板" }, { "Add Comment", "添加注释" },
	{ "Edit", "编辑" }, { "General", "常规" }, { "Guides", "指南" }, { "View", "视图" },
	{ "File", "文件" }, { "Help", "帮助" },
	{ "This will export the current selection as *.lilnut file that can be later imported", "将当前选择导出为可稍后导入的 *.lilnut 文件" },
	{ "This will import a *.lilnut file and add it to the current noisette", "导入 *.lilnut 文件并添加到当前项目" },
};

juce::StringPairArray reverseTranslations;

juce::String escapeMappingValue(const juce::String& value)
{
	return value.replace("\\", "\\\\").replace("\"", "\\\"");
}

juce::String decodeTranslationValue(const juce::String& value)
{
	// TSV keeps line breaks, tabs, and literal backslashes escaped so every
	// entry remains one row.  Decode them in one pass: "\\n" is a literal
	// backslash followed by n, while "\n" is an actual line break.
	juce::String result;
	for (int i = 0; i < value.length(); ++i)
	{
		const auto c = value[i];
		if (c != '\\' || i + 1 >= value.length())
		{
			result << c;
			continue;
		}

		const auto escaped = value[++i];
		switch (escaped)
		{
		case '\\': result << '\\'; break;
		case 'n': result << '\n'; break;
		case 'r': result << '\r'; break;
		case 't': result << '\t'; break;
		default: result << c << escaped; break;
		}
	}
	return result;
}

void loadExternalTranslationFile(juce::StringPairArray& translations)
{
	const auto applicationFile = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
	juce::Array<juce::File> candidates;
	candidates.add(applicationFile.getChildFile("Contents/Resources/ChataigneTranslations.tsv"));
	candidates.add(applicationFile.getParentDirectory().getParentDirectory().getChildFile("Resources/ChataigneTranslations.tsv"));
	candidates.add(applicationFile.getParentDirectory().getChildFile("ChataigneTranslations.tsv"));
	candidates.add(juce::File::getCurrentWorkingDirectory().getChildFile("Source/UI/ChataigneTranslations.tsv"));

	for (const auto& file : candidates)
	{
		if (!file.existsAsFile()) continue;

		juce::StringArray lines;
		lines.addLines(file.loadFileAsString());
		for (auto line : lines)
		{
			line = line.trim();
			if (line.isEmpty() || line.startsWithChar('#')) continue;

			const auto separator = line.indexOfChar('\t');
			if (separator <= 0) continue;

			const auto target = decodeTranslationValue(line.substring(0, separator).trim());
			const auto source = decodeTranslationValue(line.substring(separator + 1).trim());
			if (target.isNotEmpty() && source.isNotEmpty()) translations.set(source, target);
		}
		break;
	}
}

juce::String makeBilingualDisplayText(const juce::String& target, const juce::String& source)
{
	if (target == source) return target;
	return target + " (" + source + ")";
}

juce::String createSimplifiedChineseMapping(bool bilingual)
{
	juce::String result = "language: Simplified Chinese\ncountries: cn sg\n\n";
	// Keep keys case-sensitive.  JUCE's default StringPairArray is
	// case-insensitive, which would collapse entries such as "Next Cue" and
	// "Next cue" and leave one of the UI command variants untranslated.
	juce::StringPairArray translations(false);
	for (const auto& pair : simplifiedChineseTranslations)
	{
		const auto source = juce::String::fromUTF8(pair.source);
		const auto target = juce::String::fromUTF8(pair.target);
		translations.set(source, target);
	}

	// Keep the editable vocabulary outside the model layer.  The TSV can add
	// or override UI strings without changing project data or control addresses.
	loadExternalTranslationFile(translations);
	for (const auto& source : translations.getAllKeys())
	{
		const auto target = translations[source];
		const auto displayTarget = bilingual ? makeBilingualDisplayText(target, source) : target;
		result << "\"" << escapeMappingValue(source) << "\" = \""
			<< escapeMappingValue(displayTarget) << "\"\n";
		// A refresh may see either the plain Chinese text from a previous
		// language mode or the bilingual text just generated.  Keep both
		// forms reversible even when the newly selected mode only uses one.
		reverseTranslations.set(target, source);
		reverseTranslations.set(makeBilingualDisplayText(target, source), source);
	}
	return result;
}

void refreshComponentTree(juce::Component& component)
{
	if (auto* label = dynamic_cast<juce::Label*>(&component))
	{
		// Editable labels are user data (custom names and enum keys), not UI copy.
		if (!label->isEditable())
			label->setText(ChataigneLocalization::translateForDisplay(label->getText()), juce::dontSendNotification);
	}

	if (auto* button = dynamic_cast<juce::Button*>(&component))
		button->setButtonText(ChataigneLocalization::translateForDisplay(button->getButtonText()));

	if (auto* comboBox = dynamic_cast<juce::ComboBox*>(&component))
	{
		for (int i = 0; i < comboBox->getNumItems(); ++i)
		{
			const int itemId = comboBox->getItemId(i);
			comboBox->changeItemText(itemId, ChataigneLocalization::translateForDisplay(comboBox->getItemText(i)));
		}
	}

	if (auto* tooltipClient = dynamic_cast<juce::SettableTooltipClient*>(&component))
	{
		const auto tooltip = tooltipClient->getTooltip();
		if (tooltip.isNotEmpty())
			tooltipClient->setTooltip(ChataigneLocalization::translateForDisplay(tooltip));
	}

	const auto componentName = component.getName();
	if (componentName.isNotEmpty())
		component.setName(ChataigneLocalization::translateForDisplay(componentName));

	for (int i = 0; i < component.getNumChildComponents(); ++i)
		if (auto* child = component.getChildComponent(i)) refreshComponentTree(*child);

	component.resized();
	component.repaint();
}
}

bool ChataigneLocalization::isSimplifiedChinese()
{
	return activeLanguageId == simplifiedChineseLanguageId || activeLanguageId == bilingualChineseLanguageId;
}

bool ChataigneLocalization::isBilingual()
{
	return activeLanguageId == bilingualChineseLanguageId;
}

juce::String ChataigneLocalization::sourceText(const juce::String& text)
{
	if (reverseTranslations.containsKey(text)) return reverseTranslations[text];
	return text;
}

juce::String ChataigneLocalization::translateForDisplay(const juce::String& text)
{
	return juce::translate(sourceText(text));
}

juce::String ChataigneLocalization::translateCommandLabel(const juce::String& label)
{
	if (!isSimplifiedChinese()) return label;

	for (const auto& prefix : { juce::String("Undo "), juce::String("Redo ") })
	{
		if (!label.startsWith(prefix)) continue;

		const auto translatedPrefix = juce::translate(prefix.trimEnd());
		const auto operation = label.substring(prefix.length()).trim();
		if (operation.isEmpty()) return translatedPrefix;

		if (operation.startsWith("Set ") && operation.endsWith(" value"))
		{
			const auto parameterName = operation.substring(4, operation.length() - 6);
			const auto separator = isBilingual() ? juce::String(" ") : juce::String();
			return translatedPrefix + separator
				+ juce::translate("Set") + separator
				+ translateForDisplay(parameterName) + separator
				+ juce::translate("value");
		}

		return translatedPrefix + " " + translateForDisplay(operation);
	}

	return label;
}

void ChataigneLocalization::setLanguage(const juce::String& languageId, bool refreshExistingComponents)
{
	reverseTranslations.clear();
	activeLanguageId = languageId;
	const bool chinese = languageId == simplifiedChineseLanguageId || languageId == bilingualChineseLanguageId;
	const auto mapping = createSimplifiedChineseMapping(languageId == bilingualChineseLanguageId);
	if (chinese)
		juce::LocalisedStrings::setCurrentMappings(new juce::LocalisedStrings(mapping, false));
	else
		juce::LocalisedStrings::setCurrentMappings(nullptr);

	if (refreshExistingComponents) ChataigneLocalization::refreshAllComponents();
}

void ChataigneLocalization::refreshAllComponents()
{
	for (int i = 0; i < juce::TopLevelWindow::getNumTopLevelWindows(); ++i)
	{
		if (auto* window = juce::TopLevelWindow::getTopLevelWindow(i))
			refreshComponentTree(*window);
	}

	if (auto* app = dynamic_cast<OrganicApplication*>(juce::JUCEApplication::getInstance()))
		if (app->mainComponent != nullptr) app->mainComponent->menuItemsChanged();
}
