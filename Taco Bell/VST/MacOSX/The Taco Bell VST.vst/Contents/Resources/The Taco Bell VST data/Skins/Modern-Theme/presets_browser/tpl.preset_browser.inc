<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
  <!-- Presets Files Browser Template 
  - dest: string to hold the file path and an optional load action to load it once set.
  - dest_path_type: select the type of path (absolute or relative to root paths) to set on destination path string
  - optional add item feature: file path items can be added to a collection (add_item_collection_id) using a button, activated by show_add_button_param. Expects add_item_collection_id[].path attribute.
  -->
  <ACTION id="TPL_PRESETS_FILES_BROWSER_DoNothing" type="Script" script=""/>
  <SCRIPT src="$_DIR_$tpl.preset_browser.cxx"/>
  <SCRIPT src="$_DIR_$tpl.preset_browser.$_SYSTEM_TYPE_$.cxx"/>
  <TEMPLATE id="TPL_PRESETS_FILES_BROWSER" root_path="" file_types="" default_dir_name=""
            dest_file_path_string="#UNDEFINED#" dest_load_action="TPL_PRESETS_FILES_BROWSER_DoNothing" dest_path_type="path"
            add_item_enabled="0" add_item_collection_id="" item_added_action_id="" show_add_button_param="#UNDEFINED#"
            persistent="true" persistence_context="-Preset" preset_icon_scaling="1"
            graphics_dir="$_DIR_$">
    <!-- DATA MODEL -->
    <STRING id="$id$.current_path" default="" exposed="true" persistent="$persistent$" persistence_context="$persistence_context$"/>
    <STRING id="$id$.current_dir_name" default="" exposed="true"/>
    <COLLECTION id="$id$.files">
      <STRING id="$item_id$.name"/>
      <STRING id="$item_id$.path"/>
      <STRING id="$item_id$.absolute_path"/>
    </COLLECTION>
    <COLLECTION id="$id$.dirs">
      <STRING id="$item_id$.name"/>
      <STRING id="$item_id$.path"/>
      <STRING id="$item_id$.absolute_path"/>
    </COLLECTION>
    <STRING id="$id$.search_string" persistent="$persistent$" persistence_context="$persistence_context$"/>
    <STRING id="$id$.wildcard"/>
    <FORMULA_PARAM id="$id$.items_count" formula="$id$.dirs.count+$id$.files.count"/>

    <!-- Refresh is ASYNC because it changes the number of items so it cannot be called from within items that might be destroyed-->
    <ACTION id="$id$.Refresh" type="ScanDirectory" directory_string_id="$id$.current_path" files_collection_id="$id$.files" dirs_collection_id="$id$.dirs" root_path="$root_path$" file_types="$file_types$"/>
    <ACTION_TRIGGER event_id="$id$.current_path.value_changed" condition_formula="$id$.wildcard.length==0" action_id="$id$.Refresh" async="true"/>
    <ACTION_TRIGGER event_id="$id$.wildcard.value_changed" condition_formula="$id$.wildcard.length==0" action_id="$id$.Refresh" async="true"/>
    <ACTION_TRIGGER event_id="window.loaded.value_changed" condition_formula="(window.loaded!=0) &amp;&amp;($id$.search_string.length==0)" action_id="$id$.Refresh" />

    <ACTION id="$id$.Search" type="ScanDirectory" directory_string_id="$id$.current_path" files_collection_id="$id$.files" dirs_collection_id="$id$.dirs" recursive="true" wildcards_string_id="$id$.wildcard" root_path="$root_path$" file_types="$file_types$"/>
    <ACTION_TRIGGER event_id="$id$.current_path.value_changed" condition_formula="$id$.wildcard.length!=0" action_id="$id$.Search" async="true"/>
    <ACTION_TRIGGER event_id="$id$.wildcard.value_changed" condition_formula="$id$.wildcard.length!=0" action_id="$id$.Search" async="true"/>
    <ACTION id="$id$.EmptySearch" type="Script" script="$id$.search_string=&quot;&quot;" requires="$id$.search_string"/>
    
    <!-- pre scan and refresh actions: reset browser offset -->
    <ACTION_TRIGGER event_id="$id$.Refresh.running.value_changed" condition_formula="$id$.Refresh.running==1" script="$id$.browser_offset.y=0" requires="$id$.browser_offset.y"/>
    <ACTION_TRIGGER event_id="$id$.Search.running.value_changed" condition_formula="$id$.Search.running==1" script="$id$.browser_offset.y=0" requires="$id$.browser_offset.y"/>

    <ACTION id="$id$.UpDir" type="Script" script=" 
          string path=PresetBrowser::cleanPath($id$.current_path);
          const string separator=PresetBrowser::getFilePathSeparator();
          array&lt;string&gt; items=path.split(separator);
          if(items.length>0)
          {
            int index=items.length-1;
            while(items[index].length==0)
              index--;
            if(index>=0)
            {
              path=&quot;&quot;;  
              for(int i=0;i&lt;index;i++)
              {
                path+=items[i];
                path+=separator;
              }
              $id$.current_path=path;
            }
            else
              $id$.current_path=&quot;&quot;;
          } 
          else  
          $id$.current_path=&quot;&quot;;"
           requires="$id$.current_path"/>

    <!-- Update Current dir name -->
    <ACTION_TRIGGER event_ids="$id$.current_path.value_changed;window.loaded.value_changed" condition_formula="window.loaded!=0" type="Script" script="
          string value=PresetBrowser::cleanPath($id$.current_path);
          const string separator=PresetBrowser::getFilePathSeparator();
          array&lt;string&gt; items=value.split(separator);
          value=&quot;$default_dir_name$&quot;;
          if(items.length>0)
          {
            int index=items.length-1;
            while(index&gt;=0 &amp;&amp; items[index].length==0)
              index--;
            if(index>=0)
            {
              value=items[index];
            }
          } 
          $id$.current_dir_name=value;"
            requires="$id$.current_dir_name"/>

    <!-- Build wildcard from search string -->
    <ACTION_TRIGGER event_ids="$id$.search_string.value_changed;window.loaded.value_changed" condition_formula="window.loaded!=0" type="Script" script="
          string s=$id$.search_string;
          string outWildCard;
          /* split comma separated items*/
           array&lt;string&gt; items=s.split(&quot;,&quot;);
           for(uint i=0;i&lt;items.length;i++)
           {
             /* transform into wildcard if just a word */
              string itemString=items[i];
              if(itemString.length>0 &amp;&amp; itemString.findFirst(&quot;*&quot;)&lt;0 &amp;&amp; itemString.findFirst(&quot;?&quot;)&lt;0)
              {
                itemString=&quot;*&quot;+items[i]+&quot;*&quot;;
              }
              /* add to output */
              outWildCard+=itemString;
              if(i!=items.length-1)
                outWildCard+=&quot;;&quot;;
          }
          $id$.wildcard=outWildCard;
                  " requires="$id$.wildcard;$id$.search_string"/>

	  <!-- Open current sub directory -->
      <ACTION id="$id$.OpenCurrentSubDir" type="Script" script="
              const int count=int($id$.dirs.count);
              if(count>0)
              {
                int index=0;
                while(index&lt;count)
                {
                  if($id$.dirs[index].selected.visible==1.0)
				  {
					$id$.dirs[index].Open();
                    break;
				  }
                  index++;
                }
            }
         "
           requires="$id$.dirs.count;$id$.dirs[*].Open;$id$.dirs[*].selected.visible"/>

    <!-- Next and previous presets -->
      <ACTION id="$id$.NextPreset" type="Script" script="
              const int count=int($id$.files.count);
              if(count>0)
              {
                int index=0;
                while(index&lt;count)
                {
                  if($id$.files[index].selected.visible==1.0)
                    break;
                  index++;
                }
                index++;
                if(index>=count)
                  index=0;
              
                  $id$.files[index].Open();
            }
         "
           requires="$id$.files.count;$id$.files[*].Open;$id$.files[*].selected.visible"/>
     <ACTION id="$id$.PreviousPreset" type="Script" script="
              const int count=int($id$.files.count);
              if(count>0)
              {
                int index=count-1;
                while(index>0)
                {
                  if($id$.files[index].selected.visible==1.0)
                    break;
                  index--;
                }
                index--;
                if(index&lt;0)
                  index=count-1;
                  $id$.files[index].Open();
               }"
           requires="$id$.files.count;$id$.files[*].Open"/>
              
    <WIDGET spacing="2" height="100%" id="$id$" background_color="#252729" margin="10" width="230">
      <!-- current directory -->
      <LAYER_STACK width="100%">
        <INVISIBLE_ACTION_BUTTON id="$id$.up_dir_button" width="100%" height="100%" action_id="$id$.UpDir" cursor="system::hand">
          <TOOLTIP string_id="$id$.current_path"/>
        </INVISIBLE_ACTION_BUTTON>
        <WIDGET background_color="#17191c" layout_type="row" margin="2" h_margin="4" width="100%" internal_h_align="left" spacing="2">
          <LAYER_STACK>
            <IMAGE image="$graphics_dir$/folder_open.svg"/>
          </LAYER_STACK>
          <TEXT string_id="$id$.current_dir_name" text_color="#44b5ff" font_weight="bold" font_size="15" flex="1" text_h_align="left">
          </TEXT>
          <IMAGE image="$graphics_dir$/folder_up.svg" id="$id$.folder_icon_up"/>
          <PARAM_MULTI_LINK from="$id$.current_path.length" to="$id$.folder_icon_up.visible;$id$.up_dir_button.enabled" formula="x!=0"/>
        </WIDGET>
      </LAYER_STACK>
      <CELL height="4"/>
      <!-- Search box -->
      <WIDGET background_color="#17191c" width="100%" layout_type="row" v_margin="2"  h_margin="4" spacing="1">
        <IMAGE image="$graphics_dir$/search.svg">
          <INVISIBLE_ACTION_BUTTON id="$id$.search_button" width="100%" height="100%" action_id="$id$.Search" cursor="system::hand" auto_focus="false"/>
          <PARAM_LINK from="$id$.wildcard.length" to="$id$.search_button.enabled" formula="x!=0"/>
        </IMAGE>
        <PARAM_LINK from="$id$.visible" to="$id$.search_box.visible"/>
        <TEXT_EDIT_BOX id="$id$.search_box" string_id="$id$.search_string" background_color="#17191c" show_edges="false" text_color="#d3d3d3" flex="1" height="14" v_align="bottom"/>
        <IMAGE image="$graphics_dir$/x.svg">
          <INVISIBLE_ACTION_BUTTON width="100%" height="100%" action_id="$id$.EmptySearch" cursor="system::hand"/>
        </IMAGE>
      </WIDGET>
      <!-- Results Count and Next/Previous Preset commands -->
      <LAYER_STACK width="100%" margin="1" h_margin="2">
        <ROW spacing="5">
          <PARAM_MULTI_LINK from="$id$.files.count" to="$id$.prev_button.visible;$id$.next_button.visible" formula="x!=0"/>
          <IMAGE_ACTION_BUTTON id="$id$.prev_button" image="$graphics_dir$/arrow_left.svg" opaque_mouse_mask="true" action_id="$id$.PreviousPreset" cursor="system::hand"/>
          <PARAM_TEXT content="{text_value} presets found" param_id="$id$.files.count" text_color="#a7a7a7"/>
          <IMAGE_ACTION_BUTTON id="$id$.next_button" image="$graphics_dir$/arrow_right.svg" opaque_mouse_mask="true" action_id="$id$.NextPreset" cursor="system::hand"/>
        </ROW>
        <!-- Copy results to collection (if enabled) -->
        <REPEAT count="$add_item_enabled$">
          <PARAM_LINK from="$show_add_button_param$" to="$id$.add_all_button.visible"/>
          <IMAGE image="$graphics_dir$/plus.svg" id="$id$.add_all_button" h_align="right">
            <ACTION id="$id$.SendAll" type="Script" script="
                  auto@ items=$add_item_collection_id$;
                  uint count=uint($id$.files.count);
                  uint initial_items_count=uint(items.count);
                  array&lt;string&gt; files(count);
                  uint filesToAdd=0;
                  for(uint i=0;i&lt;count;i++)
                  {
                    string path=$id$.files[i].path;
                    bool dup=false;
                    for(uint j=0;j&lt;initial_items_count;j++)
                    {
                      if(path==items[j].path)
                      {
                        dup=true;
                        break;
                      }
                    }
                    if(!dup)
                    {
                      files[filesToAdd]=path;
                      filesToAdd++;
                    }
                  }
                  items.count+=filesToAdd;
                  for(uint i=0;i&lt;filesToAdd;i++)
                  {
                    items[initial_items_count+i].path=files[i];
                  }
                  if(initial_items_count!=uint(items.count))
                    $item_added_action_id$();
                  " requires="$add_item_collection_id$.count;$add_item_collection_id$[].path;$id$.files.count;$id$.files[].path"/>
            <INVISIBLE_ACTION_BUTTON action_id="$id$.SendAll" width="100%" height="100%" cursor="system::hand">
              <PARAM_TOOLTIP param_id="$id$.files.count" content="Add {text_value} presets to map"/>
            </INVISIBLE_ACTION_BUTTON>
          </IMAGE>
        </REPEAT>

      </LAYER_STACK>

      <!-- Results area with scrollbar-->
      <WIDGET background_color="#141518" width="100%" flex="1" margin="1" layout_type="row">
        <WIDGET id="$id$.browser_outer_area" flex="1" height="100%" layout_type="layer_stack" background_color="#141518">
          <PARAM id="$id$.browser_offset.y" default="0" min="0" max="1" name="Scroll Position"/>
          <FORMULA_PARAM id="$id$.browser_area_height_diff" formula="max(0,$id$.browser_area.height-$id$.browser_outer_area.height)"/>
          <FORMULA_PARAM id="$id$.browser_area_v_offset" formula="-$id$.browser_area_height_diff*$id$.browser_offset.y"/>
          <PARAM_LINK from="$id$.browser_area_v_offset" to="$id$.browser_area.v_offset"/>

          <WIDGET id="$id$.browser_area" background_color="#141518" width="100%" v_position="0" layout_type="layer_stack">
            <XYZ_PARAM_SCRATCH_PAD y_param_id="$id$.browser_offset.y" z_param_id="$id$.browser_offset.y" z_reverse="true" width="100%" height="100%" id="$id$.browser_pad" default_keys_enabled="false" handled_keys="ArrowDown;ArrowUp;ArrowLeft;ArrowRight;ArrowRight"/>
			<ACTION_TRIGGER event_id="$id$.browser_pad.key_pressed" condition_formula="$id$.browser_pad.key_pressed.key!=0" script="
			  gui.BeginCapture();
			  if($id$.browser_pad.key_pressed.key.text_value==&quot;ArrowUp&quot;) $id$.PreviousPreset(); 
			  else if($id$.browser_pad.key_pressed.key.text_value==&quot;ArrowDown&quot;) $id$.NextPreset();
			  else if($id$.browser_pad.key_pressed.key.text_value==&quot;ArrowLeft&quot;) $id$.UpDir();
			  else if($id$.browser_pad.key_pressed.key.text_value==&quot;ArrowRight&quot;) $id$.OpenCurrentSubDir();
			  gui.EndCapture();" 
			  requires="$id$.browser_pad.key_pressed.key.text_value;$id$.PreviousPreset;$id$.NextPreset;$id$.UpDir;$id$.OpenCurrentSubDir;gui.BeginCapture;gui.EndCapture;"/>

            <PARAM_LINK from="$id$.browser_area_height_diff" to="$id$.browser_pad.y_pixel_range" formula="x*$PIXEL_SCALE_FACTOR$"/>
            <COLUMN width="100%">
              <COLUMN width="100%" text_color="#44b5ff" spacing="1">
                <!-- Directories List -->
                <FOREACH collection_id="$id$.dirs">
                  <WIDGET layout_type="layer_stack" width="100%" background_color="#17191c">
                    <INVISIBLE_ACTION_BUTTON width="100%" height="100%" action_id="$$id$.dirs_item_id$.Open" cursor="system::hand" accept_focus="false"/>
                    <ACTION id="$$id$.dirs_item_id$.Open" type="Script" script="$id$.current_path=$$id$.dirs_item_id$.path" requires="$$id$.dirs_item_id$.path"/>
                    <ACTION_TRIGGER event_id="$$id$.dirs_item_id$.Open.running.value_changed" condition_formula="$$id$.dirs_item_id$.Open.running==0" action_id="$id$.EmptySearch"/>
                    <LAYER_STACK h_align="left">
                      <ROW h_margin="2">
                        <LAYER_STACK>
                          <IMAGE image="$graphics_dir$/folder_closed.svg" id="$$id$.dirs_item_id$.not_selected" visible="true"/>
                          <IMAGE image="$graphics_dir$/folder_open.svg" id="$$id$.dirs_item_id$.selected" visible="false"/>
                          <PARAM_LINK from="$$id$.dirs_item_id$.selected.visible" to="$$id$.dirs_item_id$.not_selected.visible" reverse="true"/>
                        </LAYER_STACK>
                        <TEXT string_id="$$id$.dirs_item_id$.name"/>
                      </ROW>                    
                    </LAYER_STACK>
                    <!-- Current dir selection -->
                    <ACTION_TRIGGER event_ids="$dest_file_path_string$.value_changed;$$id$.dirs_item_id$.$dest_path_type$.value_changed" type="Script" script="
                   string dest=PresetBrowser::cleanPath($dest_file_path_string$);
                   string path=PresetBrowser::cleanPath($$id$.dirs_item_id$.$dest_path_type$);
                    const string separator=PresetBrowser::getFilePathSeparator();
                   if(path.findLast(separator)!=path.length-1)
                      path+=separator;
                  if(dest.findFirst(path)==0)
                    $$id$.dirs_item_id$.selected.visible=1;
                  else
                    $$id$.dirs_item_id$.selected.visible=0;
                  " requires="$dest_file_path_string$;$$id$.dirs_item_id$.$dest_path_type$;$$id$.dirs_item_id$.selected.visible"/>
                  </WIDGET>
                </FOREACH>
              </COLUMN>

              <!-- Files List -->
			  <EXPOSED_OBJECTS object_ids="$id$.files_list_cell.v_position;$id$.browser_offset.y;$id$.browser_outer_area.height;$id$.browser_area.height;$id$.browser_area_height_diff"/>
              <COLUMN width="100%" spacing="2" text_color="#d3d3d3" id="$id$.files_list_cell">
                <FOREACH id="$id$.files_widgets" collection_id="$id$.files">
                  <WIDGET layout_type="layer_stack" width="100%" background_color="#17191c" id="$$id$.files_item_id$.widget">
                    <WIDGET background_color="#244860" id="$$id$.files_item_id$.selected" visible="false" width="100%" height="100%"/>
					<INVISIBLE_ACTION_BUTTON width="100%" height="100%" action_id="$$id$.files_item_id$.Open" cursor="system::hand" accept_focus="false"/>
                    <ACTION id="$$id$.files_item_id$.Open" type="Script" script="$dest_file_path_string$=$$id$.files_item_id$.$dest_path_type$;$dest_load_action$();" requires="$dest_file_path_string$;$$id$.files_item_id$.$dest_path_type$;$dest_load_action$"/>
                    <!-- Current file selection -->
                    <ACTION_TRIGGER event_ids="$dest_file_path_string$.value_changed;$$id$.files_item_id$.$dest_path_type$.value_changed" type="Script" script="
                  string dest=$dest_file_path_string$;
                  if(dest==$$id$.files_item_id$.$dest_path_type$)
				  {
                    $$id$.files_item_id$.selected.visible=1;
					/*scroll to make visible in list*/
					double diff=$id$.browser_area_height_diff;
					if(diff&gt;0)
					{
						double minPos=$id$.files_list_cell.v_position+$$id$.files_item_id$.widget.v_position;
						double maxPos=minPos+$$id$.files_item_id$.widget.height;
						if(minPos&lt;diff*$id$.browser_offset.y)
						{
							$id$.browser_offset.y=minPos/diff;
						}
						else if(maxPos&gt;($id$.browser_outer_area.height+diff*$id$.browser_offset.y))
						{
							$id$.browser_offset.y=(maxPos-$id$.browser_outer_area.height)/diff;
						}
					}
				  }
                  else
                    $$id$.files_item_id$.selected.visible=0;" requires="$dest_file_path_string$;$$id$.files_item_id$.$dest_path_type$;$$id$.files_item_id$.selected.visible;$$id$.files_item_id$.widget.v_position;$$id$.files_item_id$.widget.height"/>
                    <ROW width="100%" internal_h_align="left" h_margin="2">
                        <ROW spacing="3">
                          <IMAGE image="$preset_icon$" image_scaling="$preset_icon_scaling$"/>
                          <TEXT string_id="$$id$.files_item_id$.name" flex="1" text_h_align="left"/>                            
                        </ROW>
                      <REPEAT count="$add_item_enabled$">
                        <PARAM_LINK from="$show_add_button_param$" to="$$id$.files_item_id$.add_button.visible"/>
                        <CELL flex="1"/>
                        <IMAGE image="$graphics_dir$/plus.svg" id="$$id$.files_item_id$.add_button">
                          <!-- Send / Add action if enabled -->
                          <ACTION id="$$id$.files_item_id$.Send" type="Script" script="
                    auto@ items=$add_item_collection_id$;
                    string path=$$id$.files_item_id$.path;
                    bool dup=false;
                    uint initial_items_count=uint(items.count);
                    for(uint j=0;j&lt;initial_items_count;j++)
                    {
                      if(path==items[j].path)
                      {
                        dup=true;
                        break;
                      }
                    }
                    if(!dup)
                    {
                      items.count++;
                      items[uint(items.count-1)].path=path;
                    }
                    if(initial_items_count!=uint(items.count))
                      $item_added_action_id$();" requires="$add_item_collection_id$.count;$add_item_collection_id$[].path;$id$.files.count;$$id$.files_item_id$.path"/>
                          <INVISIBLE_ACTION_BUTTON action_id="$$id$.files_item_id$.Send" width="100%" height="100%" cursor="system::hand">
                          </INVISIBLE_ACTION_BUTTON>
                        </IMAGE>
                      </REPEAT>
                    </ROW>
                  </WIDGET>
                </FOREACH>
              </COLUMN>
            </COLUMN>
          </WIDGET>
        </WIDGET>
        <!-- scrollbar -->
        <WIDGET id="$id$.browser_area.scrollbar" width="12" height="100%" background_color="#111315" v_margin="1" h_margin="2" layout_type="row">
          <CELL width="1"/>
          <COLUMN flex="1" height="100%">
            <INVISIBLE_PARAM_BUTTON id="$id$.browser_area.scrollbar.pre_thumb" width="100%" height="0" param_id="$id$.browser_offset.y"
                                    reverse="true" cursor="system::hand" loop="false"/>
            <WIDGET id="$id$.browser_area.scrollbar.thumb" width="100%" height="100%" background_color="#252729">
              <XYZ_PARAM_SCRATCH_PAD id="$id$.browser_area.scrollbar_control" y_param_id="$id$.browser_offset.y" z_param_id="$id$.browser_offset.y" y_reverse="true" z_reverse="true" width="100%" height="100%" cursor="system::hand"/>
            </WIDGET>
            <INVISIBLE_PARAM_BUTTON id="$id$.browser_area.scrollbar.post_thumb" flex="1" width="100%" height="0"
                                    param_id="$id$.browser_offset.y" cursor="system::hand" loop="false"/>
          </COLUMN>
          <!-- Scrollbar length, offset and visibility-->
          <FORMULA_PARAM id="$id$.browser_area.scrollbar_length" formula="round($id$.browser_area.scrollbar.height*$id$.browser_outer_area.height/$id$.browser_area.height)"/>
          <PARAM_LINK from="$id$.browser_area.scrollbar_length" to="$id$.browser_area.scrollbar.thumb.height"/>
          <FORMULA_PARAM id="$id$.browser_area.scrollbar_diff" formula="$id$.browser_area.scrollbar.height-$id$.browser_area.scrollbar_length-2*$id$.browser_area.scrollbar.v_margin"/>
          <FORMULA_PARAM id="$id$.browser_area.scrollbar_offset" formula="round($id$.browser_offset.y*$id$.browser_area.scrollbar_diff)"/>
          <PARAM_LINK from="$id$.browser_area.scrollbar_offset" to="$id$.browser_area.scrollbar.pre_thumb.height"/>
          <PARAM_LINK from="$id$.browser_area.scrollbar_diff" to="$id$.browser_area.scrollbar_control.y_pixel_range" formula="x*$PIXEL_SCALE_FACTOR$"/>
          <PARAM_LINK from="$id$.browser_area.scrollbar_diff" to="$id$.browser_area.scrollbar.display" formula="x>0"/>
          <!-- positions count -->
          <FORMULA_PARAM id="$id$.browser_area.visible_lines_count" formula="($id$.items_count)*$id$.browser_outer_area.height/$id$.browser_area.height"/>
          <FORMULA_PARAM id="$id$.browser_area.scrollbar_positions_count" formula="round(($id$.items_count)-$id$.browser_area.visible_lines_count)+1"/>
          <PARAM_MULTI_LINK from="$id$.browser_area.scrollbar_positions_count" to="$id$.browser_area.scrollbar_control.z_positions_count;$id$.browser_area.scrollbar_control.y_positions_count;$id$.browser_pad.y_positions_count;$id$.browser_pad.z_positions_count"/>
          <FORMULA_PARAM id="$id$.browser_area.pages_count" formula="ceil($id$.browser_area.height/$id$.browser_outer_area.height)"/>
          <PARAM_MULTI_LINK from="$id$.browser_area.pages_count" to="$id$.browser_area.scrollbar.pre_thumb.positions_count;$id$.browser_area.scrollbar.post_thumb.positions_count"/>
        </WIDGET>
      </WIDGET>
    </WIDGET>
  </TEMPLATE>
</DUMMY>