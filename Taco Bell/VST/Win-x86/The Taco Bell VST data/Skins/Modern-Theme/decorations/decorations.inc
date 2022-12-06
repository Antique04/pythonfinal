<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
  <DEFINE>
    <DECORATIONS_STYLE_CELL base_type="CELL" font_face="Arial" font_size="11" text_color="#bcddf4" font_quality="cleartype" font_size_mode="character" />
  </DEFINE> 
  <!--Main Layout with background and decorations-->
  <TEMPLATE id="TPL_DECORATIONS" title="$PLUGIN_NAME$" spacing="0" minimum_width="400" h_margin="0" v_margin="0" show_handles="true" show_statusbar="true" text_color="#bcddf4" bg_color=""  link_text="www.bluecataudio.com" status_bar_widget="">
    <DEFINE>
      <_LOCAL_STATUSBAR_ITEMS_ base_type="$status_bar_widget$"/>
    </DEFINE>
    <DECORATIONS_STYLE_CELL layout_type="column" text_color="$text_color$">
      <LAYER_STACK>
        <!-- Background with additional texture on top -->
        <KUIML_WIDGET id="theme.decorations.background" src="custom_bg.kuiml.inc" width="100%" height="100%"/>
        
        <!-- Main column, with 20 px margins minimum for L/R handles and screws-->
        <LOCAL_VARIABLE id="local_h_margin" formula="20+$h_margin$"/>
        <CELL layout_type="column" h_margin="$local_h_margin$" spacing="$spacing$" v_margin="$v_margin$" id="theme.decorations.inner_cell">
          <!-- to ensure minimum width for the toolbar and title: dummy cell-->
          <CELL width="$minimum_width$"/>
          <!-- The actual skin content -->
          <TEMPLATE_INNER_CONTENT/>
          
        </CELL>
        
        <!-- Extra widgets -->
        <!-- the 4 screws -->
        <LAYER_STACK flex="1" id="theme.decorations.screws">
          <CELL margin="4" v_align="top" h_align="left">
          <IMAGE image="$THEME_PATH$/decorations/screw_small.png" image_scaling=".5" ignore_mask_files="true"/>
        </CELL>
        <CELL margin="4" v_align="top" h_align="right">
          <IMAGE image="$THEME_PATH$/decorations/screw_small.png" image_scaling=".5" ignore_mask_files="true" />
        </CELL>
        <CELL margin="4" v_align="bottom" h_align="left">
          <IMAGE image="$THEME_PATH$/decorations/screw_small.png" image_scaling=".5" ignore_mask_files="true" />
        </CELL>
        <CELL margin="4" v_align="bottom" h_align="right">
          <IMAGE image="$THEME_PATH$/decorations/screw_small.png" image_scaling=".5" ignore_mask_files="true" />
        </CELL>
        </LAYER_STACK> 
        <!-- the two handles on top of the design, aligned to left and right-->
        <LAYER_STACK flex="1" id="theme.decorations.handles">
          <COLUMN h_align="left" height="100%" v_margin="4">
            <CELL height="40" />
            <IMAGE_GROUP_BOX image="$THEME_PATH$/decorations/handle_left.png" flex="1" width="20" ignore_mask_files="true" display="$show_handles$" id="theme.decorations.handle_left"/>
            <PARAM_LINK from="theme.decorations.handle_left.height" to="theme.decorations.handle_left.visible" formula="x>=90"/>
            <CELL height="40" />
          </COLUMN>
          <COLUMN h_align="right" height="100%" v_margin="4">
            <CELL height="40" />
            <IMAGE_GROUP_BOX image="$THEME_PATH$/decorations/handle_right.png" flex="1" width="20" ignore_mask_files="true" display="$show_handles$" id="theme.decorations.handle_right"/>
            <PARAM_LINK from="theme.decorations.handle_right.height" to="theme.decorations.handle_right.visible" formula="x>=90"/>
            <CELL height="40" />
          </COLUMN>
        </LAYER_STACK>
      </LAYER_STACK>
      
      <!-- Bottom status bar-->
      <LAYER_STACK width="100%">
      <IMAGE_GROUP_BOX id="theme.decorations.status_bar" image="$THEME_PATH$/decorations/status_bar.png" width="100%" height="24" font_size="11" font_face="Arial" ignore_mask_files="true" layout_type="layer_stack" display="$show_statusbar$">
              <TEXT value="$link_text$" text_color="#666666">
                <INVISIBLE_ACTION_BUTTON action_id="OpenWebsite" width="100%" height="100%" cursor="system::hand" id="website"/>
              </TEXT>
              <TEXT value="$link_text$" opacity="0" text_color="#cccccc" id="theme.website_hi"/>
              <PARAM_ANIMATOR param_id="theme.website_hi.opacity" id="theme.website_hi.opacity_animated" duration_ms="300"/>
              <PARAM_LINK from="website.mouse_over" to="theme.website_hi.opacity_animated" formula=".7*x"/>
              <_LOCAL_STATUSBAR_ITEMS_/>
       </IMAGE_GROUP_BOX>
        <CELL height="2"/>
      </LAYER_STACK>
    </DECORATIONS_STYLE_CELL>
    <UNDEFINE>
      <_LOCAL_STATUSBAR_ITEMS_/>
    </UNDEFINE>
  </TEMPLATE>
</DUMMY>