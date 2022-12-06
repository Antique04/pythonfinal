// utility to replace a string
void replaceString(string & ioString,const string &in stringToFind,const string &in replaceString)
{
    array<string>@ pieces=ioString.split(stringToFind);
    if(@pieces!=null)
    {
      if(pieces.length>0)
        ioString=pieces[0];
      for(uint i=1;i<pieces.length;i++)
      {
          ioString+=replaceString;
          ioString+=pieces[i];
      }
    }
}

string LoadTemplate()
{
    file f;
    string content;
    if(f.open("$_DIR_$/controls_skin_template.inc","r")>=0)
    {
       content=f.readString(f.getSize());
       f.close();
    }
    return content;
}

string templateContent=LoadTemplate();

string GetKnobStyle(uint style)
{
    switch (style)
    {
    case 0:
        return "PNS_SILVER_BLUE_MODERN_KNOB";
    case 1:
        return "PNS_SILVER_PINK_MODERN_KNOB";
    case 2:
        return "PNS_BLACK_BLUE_MODERN_KNOB";
    case 3:
        return "PNS_BLACK_PINK_MODERN_KNOB";
    case 4:
        return "PNS_BLACK_VINTAGE_B_KNOB";
    case 5:
        return "PNS_BLACK_CHICKEN_B_KNOB";
    case 6:
        return "PNS_WHITE_CHICKEN_B_KNOB";
    case 7:
        return "PNS_CREAM_CHICKEN_B_KNOB";
    case 8:
        return "PNS_WHITE_STOVE_KNOB";
    case 9:
        return "PNS_BLACK_STOVE_KNOB";
    case 10:
        return "PNS_BLACKORANGE_STOVE_KNOB";
    case 11:
        return "PNS_ORANGE_STOVE_KNOB";
    case 12:
        return "PNS_BLACK_SKIRTED_B_KNOB";
    case 13:
        return "PNS_SILVER_KNOB";
    case 14:
        return "PNS_GOLD_KNOB";
    case 15:
        return "PNS_GREY_FLAT_KNOB";
    case 16:
        return "PNS_BLUE_FLAT_KNOB";
    case 17:
        return "PNS_ORANGE_FLAT_KNOB";
    case 18:
        return "PNS_YELLOW_FLAT_KNOB";   
    case 19:
        return "PNS_GREEN_FLAT_KNOB";  
    case 20:
        return "PNS_RED_FLAT_KNOB";   
    }
    return "PNS_SILVER_BLUE_MODERN_KNOB";
}

string GetSwitchStyle(uint style)
{
    switch (style)
    {
    case 0:
        return "PNS_VSELECT_SWITCH";
    case 1:
        return "PNS_VSELECT_SWITCH";
    case 2:
        return "PNS_CLASSIC_SWITCH";
    case 3:
        return "PNS_CLASSIC_SWITCH";
    case 4:
        return "PNS_VINTAGE_SWITCH";
    case 5:
        return "PNS_VINTAGE_SWITCH";
    case 6:
        return "PNS_VINTAGE_SWITCH";
    case 7:
        return "PNS_VINTAGE_SWITCH";
    case 8:
        return "PNS_CLASSIC_SWITCH";
    case 9:
        return "PNS_CLASSIC_SWITCH";
    case 10:
        return "PNS_CLASSIC_SWITCH";
    case 11:
        return "PNS_CLASSIC_SWITCH";
    case 12:
        return "PNS_VINTAGE_SWITCH";
    case 13:
        return "PNS_VINTAGE_SWITCH";
    case 14:
        return "PNS_VINTAGE_SWITCH";
    case 15:
        return "PNS_CLASSIC_SWITCH";
    case 16:
        return "PNS_CLASSIC_SWITCH";
    case 17:
        return "PNS_CLASSIC_SWITCH";
    case 18:
        return "PNS_CLASSIC_SWITCH";   
    case 19:
        return "PNS_CLASSIC_SWITCH";  
    case 20:
        return "PNS_CLASSIC_SWITCH";   
    }
    return "PNS_CLASSIC_SWITCH";
}

string GetMeterStyle(uint style)
{
    switch (style)
    {
    case 0:
        return "PNS_RED_LED";
    case 1:
        return "PNS_BLUE_LED";
    case 2:
        return "PNS_GREEN_LED";
    case 3:
        return "PNS_ORANGE_LED";
    case 4:
        return "PNS_SMALL_RED_LED";
    case 5:
        return "PNS_ANALOG_VU";
    case 6:
        return "PNS_ANALOG_VU_SQUARE";
    }
    return "PNS_RED_LED";
}

string GetGroupingStyle(uint style)
{
    switch (style)
    {
    case 0:
        return "PNS_DASHED_GROUP_BOX";
    case 1:
        return "PNS_PLAIN_GROUP_BOX";
    case 2:
        return "PNS_FILLED_GROUP_BOX";
    }
    return "PNS_DASHED_GROUP_BOX";
}

string GetTextColor(uint style)
{
    switch (style)
    {
    case 0:
        return "#eaeaea";
    case 1:
        return "#aaaaaa";
    case 2:
        return "#111111";
    case 3: // blue
        return "#57bbfc";
    case 4: // orange
        return "#ffa569";
    case 5: // yellow
        return "#f2f487";
    case 6: // green
        return "#77da74";
    case 7:  // red
        return "#f64253";
    }
    return "#eaeaea";
}

string GetTextSize(int style)
{
    switch (style)
    {
    case -2:
        return "9";
    case -1:
        return "10";
    case 0:
        return "11";
    case 1:
        return "13";
    case 2:
        return "15";
    case 3:
        return "18";
    }
    return "11";
}

void GenerateControls()
{
    string content;
    if (gui_gen.enable_custom_gui!=0 && $script_gui_path$.length > 0)
    {
        // open the file
        file f;
        if (f.open($script_gui_path$, "r") >= 0)
        {
            // read content
            content=f.readString(f.getSize());
            f.close();

            // add SCRIPT_DATA_PATH variable definition, when in edit mode (already defined otherwise)
            string editMode="$SCRIPT_EDIT_MODE$";
            if (editMode == "true")
            {
                // generate SCRIPT_DATA_PATH variable
                string dataPath = $script_file_path$;
                int index = dataPath.findLast(".");
                if (index > 0)
                {
                    dataPath = dataPath.substr(0, index);
                }
                dataPath+="-data";

                // insert into skin after the SKIN tag
                string variableString = "\n<IF_EDITABLE><VARIABLE id=\"SCRIPT_DATA_PATH\" value=\"" + dataPath + "\"/></IF_EDITABLE>\n";
                int skinTagIndex=content.findFirst("<SKIN");
                if (skinTagIndex >= 0)
                {
                    skinTagIndex=content.findFirst(">",skinTagIndex);
                    if (skinTagIndex >= 0)
                    {
                        skinTagIndex++;
                        content.insert(skinTagIndex,variableString);
                    }
                }
            }
        }
    }
    else
    {
        content = templateContent;
        // number of parameters
        string value = int($script_input_params_count$);
        replaceString(content, "#in_params_count#", value);
        value = int($script_output_params_count$);
        replaceString(content, "#out_params_count#", value);

        // grid dimensions & grouping
        value = int(x_controls_display_count);
        replaceString(content, "#x_controls_display_count#", value);
        value = int(y_controls_display_count);
        replaceString(content, "#y_controls_display_count#", value);
        value = int(x_groups_count);
        replaceString(content, "#x_groups_count#", value);
        value = int(y_groups_count);
        replaceString(content, "#y_groups_count#", value);
        value = int(gui_gen.groups_display_count);
        replaceString(content, "#x_group_size#", value);
        value = int(y_group_size);
        replaceString(content, "#y_group_size#", value);
        value = int(x_last_group_size);
        replaceString(content, "#x_last_group_size#", value);
        value = int(y_last_group_size);
        replaceString(content, "#y_last_group_size#", value);

        // styles
        uint style = uint(gui_gen.controls_style);
        replaceString(content, "#knob_style#", GetKnobStyle(style));
        replaceString(content, "#switch_style#",GetSwitchStyle(style));
        style=uint(gui_gen.meters_style);
        replaceString(content, "#meter_style#",GetMeterStyle(style));
        style = uint(gui_gen.grouping_style);
        replaceString(content, "#grouping_style#", GetGroupingStyle(style));
        uint textColorValue = uint(gui_gen.text_color);
        replaceString(content, "#text_color#", GetTextColor(textColorValue));
        int textSize = int(gui_gen.text_size);
        replaceString(content, "#text_size#", GetTextSize(textSize));
        uint int_layout_type=uint(gui_gen.layout_type);
        replaceString(content, "#layout_type_int#", formatUInt(int_layout_type));
        switch (int_layout_type)
        {
        case 0:
        {
            replaceString(content, "#x_length#", "width");
            replaceString(content, "#y_length#", "height");
            replaceString(content, "#layout_type_text#", "column");
            replaceString(content, "#other_layout_type_text#", "row");
            break;
        }
        case 1:
        default:
        {
            replaceString(content, "#x_length#", "height");
            replaceString(content, "#y_length#", "width");
            replaceString(content, "#layout_type_text#", "row");
            replaceString(content, "#other_layout_type_text#", "column");
            break;
        }
        }

    }
    controls_widget.innerKUIML=content;
}

string GetBgColor(uint style)
{
    switch (style)
    {
    case 0:
        return "";
    case 1:
        return "black";
    case 2:
        return "dark-blue";
    case 3:
        return "green";
    case 4:
        return "grey";
    case 5:
        return "khaki";
    case 6:
        return "old-blue";
    case 7:
        return "orange";
    case 8:
        return "pink";
    case 9:
        return "purple";
    case 10:
        return "red";
    case 11:
        return "turquoise";
    }
    return "";
}

void GenerateBackground()
{
    string bg_color=GetBgColor(uint(gui_gen.background_color));
    string bgKUIML="";
    switch (uint(gui_gen.background_style))
    {
    //None
    case 2:
    {
        bgKUIML = "<SKIN></SKIN>";
        break;
    }
    //flat
    case 1:
    {
        bgKUIML = "<SKIN width=\"100%\" height=\"100%\" h_margin=\"3\"><IMAGE image=\"$THEME_NAME$-Theme/decorations/" + bg_color + "/bg_center.png\" repeat=\"true\" width=\"100%\" height=\"100%\" ignore_mask_files=\"true\"/></SKIN>";
        break;
    }
    // hardware is default
    case 0:
    default:
    {
        bgKUIML = "<SKIN width=\"100%\" height=\"100%\"><IMAGE_GROUP_BOX image=\"$THEME_NAME$-Theme/decorations/" + bg_color + "/bg.png\" stretch=\"false\" width=\"100%\" height=\"100%\" ignore_mask_files=\"true\"/></SKIN>";
        break;
    }
    }
    theme.decorations.background.innerKUIML=bgKUIML;
}

//string debugFilePath="$_DIR_$/debug.txt";

void GenerateExtraDataToTemp(const string& tempDir)
{
    if (tempDir.length > 0)
    {
        // write kuiml files for controls and background
        {
            string filePath = tempDir + "/Skins/custom_controls.kuiml.inc";
            file f;
            f.open(filePath, "w");
            f.writeString(controls_widget.innerKUIML);
            f.close();
        }
        {
            string filePath = tempDir + "/Skins/custom_bg.kuiml.inc";
            file f;
            f.open(filePath, "w");
            f.writeString(theme.decorations.background.innerKUIML);
            f.close();
        }
        // write constants file using current values
        {
            file f;
            string content;
            if(f.open("$_DIR_$/constants_skin_template.inc","r")>=0)
            {
                content=f.readString(f.getSize());
                f.close();
            }
            int value = uint($show_levels$);
            replaceString(content, "#display_levels#", formatUInt(value));
            value = uint(display_script_title);
            replaceString(content, "#display_script_title#", formatUInt(value));
            value = uint(display_status_bar);
            replaceString(content, "#display_status_bar#", formatUInt(value));
            value = uint(display_handles);
            replaceString(content, "#display_handles#", formatUInt(value));
            value = uint(display_screws);
            replaceString(content, "#display_screws#", formatUInt(value));
            value = uint(display_logo);
            replaceString(content, "#display_logo#", formatUInt(value));
            value = uint(gui_gen.background_style);
            replaceString(content, "#background_style_default#", formatUInt(value));
            {
                string filePath = tempDir + "/Skins/constants.inc";
                if(f.open(filePath,"w")>=0)
                {
                    f.writeString(content);
                    f.close();
                }
            }
        }
        // write pdf manual if any
        if($script_doc_path$.length>=4)
        {
            string srcPath=$script_doc_path$;
            if (srcPath.findLast(".pdf") == int(srcPath.length) - 4)
            {
                file srcFile;
                if (srcFile.open(srcPath, "r") >= 0)
                {
                    string destPath = tempDir + "/manual.pdf";
                    file destFile;
                    if (destFile.open(destPath, "w") >= 0)
                    {
                        while (!srcFile.isEndOfFile())
                        {
                            destFile.writeUInt(srcFile.readUInt(1), 1);
                        }
                        destFile.close();
                    }
                    srcFile.close();
                }
            }
        }
    }

}