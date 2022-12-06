<?xml version="1.0" encoding="utf-8" ?>
<DUMMY>
    <!-- General variables *****************************************************-->
    <VARIABLE id="input_channels_count" value="$PLUGIN_AUDIO_INPUTS_COUNT$"/>
    <VARIABLE id="output_channels_count" value="$PLUGIN_AUDIO_OUTPUTS_COUNT$"/>
    <!-- defined by plugin: SCRIPT_PARAMS_COUNT, SCRIPT_STRINGS_COUNT, SCRIPT_OUT_PARAMS_COUNT -->
    <VARIABLE id="HAS_EXTRA_INPUT_PARAMS" formula="$SCRIPT_PARAMS_COUNT$!=($PLUGIN_INPUT_PARAMS_COUNT$-1)"/>

    <!-- Basic definitions based on channels/bands count ***********************-->
    <DEFINE>
        <FOR_EACH_IN_CHANNEL base_type="REPEAT" count="$input_channels_count$" index_name="channel_index" start="1"/>
        <FOR_EACH_OUT_CHANNEL base_type="REPEAT" count="$output_channels_count$" index_name="channel_index" start="1"/>
        <IF_EDITABLE base_type="REPEAT" count="$SCRIPT_EDIT_MODE$==true" index_name="__dummy"/>
        <IF_NOT_EDITABLE base_type="REPEAT" count="$SCRIPT_EDIT_MODE$==false" index_name="__dummy"/>
    </DEFINE>

    <!-- The mapping utilities that define the NEXT_ / CURRENT_ macros-->
    <INCLUDE_ONCE file="mapping_utils.inc"/>

    <!-- Input Parameters ******************************************************-->
    <NEXT_INPUT_PARAM id="bypass"/>
    <REPEAT count="$HAS_EXTRA_INPUT_PARAMS$">
      <NEXT_INPUT_PARAM id="reload_script"/>
      <NEXT_INPUT_PARAM id="show_levels"/>
      <NEXT_INPUT_PARAM id="reserved3"/>
      <NEXT_INPUT_PARAM id="reserved4"/>
      <NEXT_INPUT_PARAM id="reserved5"/>
      <NEXT_INPUT_PARAM id="reserved6"/>
    <NEXT_INPUT_PARAM id="reserved7"/>
    </REPEAT>
    <REPEAT count="$SCRIPT_PARAMS_COUNT$">
        <NEXT_INPUT_PARAM id="script_input$index$"/>
    </REPEAT>

    <!-- Input Strings ******************************************************-->
    <NEXT_INPUT_STRING id="script_file_selection"/>
    <REPEAT count="$SCRIPT_STRINGS_COUNT$">
        <NEXT_INPUT_STRING id="script_input_string$index$"/>
    </REPEAT>

    <!-- Private Output Parameters ******************************************************-->
    <NEXT_PRIVATE_OUTPUT_PARAM id="script_status"/>
    <NEXT_PRIVATE_OUTPUT_PARAM id="script_input_params_count"/>
    <NEXT_PRIVATE_OUTPUT_PARAM id="script_output_params_count"/>
    <REPEAT count="$SCRIPT_PARAMS_COUNT$">
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_input_param$index$_min"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_input_param$index$_max"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_input_param$index$_default"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_input_param$index$_steps"/>
    </REPEAT>
    <REPEAT count="$SCRIPT_OUT_PARAMS_COUNT$">
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_output_param$index$_min"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_output_param$index$_max"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="script_output_param$index$_default"/>
    </REPEAT>
    <FOR_EACH_IN_CHANNEL>
        <NEXT_PRIVATE_OUTPUT_PARAM id="input_level$channel_index$"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="input_hold_level$channel_index$"/>
    </FOR_EACH_IN_CHANNEL>
    <FOR_EACH_OUT_CHANNEL>
        <NEXT_PRIVATE_OUTPUT_PARAM id="output_level$channel_index$"/>
        <NEXT_PRIVATE_OUTPUT_PARAM id="output_hold_level$channel_index$"/>
    </FOR_EACH_OUT_CHANNEL>
    <NEXT_PRIVATE_OUTPUT_PARAM id="script_input_strings_count"/>
  <NEXT_PRIVATE_OUTPUT_PARAM id="script_output_strings_count"/>
  <NEXT_PRIVATE_OUTPUT_PARAM id="script_file_type"/>

    <!-- Output Parameters ******************************************************-->
    <REPEAT count="$SCRIPT_OUT_PARAMS_COUNT$">
        <NEXT_OUTPUT_PARAM id="script_output$index$"/>
    </REPEAT>

    <!-- Output Strings ******************************************************-->
    <NEXT_OUTPUT_STRING id="script_status_string"/>
    <NEXT_OUTPUT_STRING id="script_name_string"/>
    <NEXT_OUTPUT_STRING id="script_description_string"/>
    <NEXT_OUTPUT_STRING id="script_author_string"/>
    <NEXT_OUTPUT_STRING id="script_file_path"/>
    <NEXT_OUTPUT_STRING id="log_file_path"/>
    <NEXT_OUTPUT_STRING id="script_doc_path"/>
    <NEXT_OUTPUT_STRING id="script_gui_path"/>

    <REPEAT count="$SCRIPT_PARAMS_COUNT$">
        <NEXT_OUTPUT_STRING id="script_input_param$index$_name"/>
        <NEXT_OUTPUT_STRING id="script_input_param$index$_unit"/>
        <NEXT_OUTPUT_STRING id="script_input_param$index$_enum_values"/>
        <NEXT_OUTPUT_STRING id="script_input_param$index$_value_format"/>
    </REPEAT>
    <REPEAT count="$SCRIPT_OUT_PARAMS_COUNT$">
        <NEXT_OUTPUT_STRING id="script_output_param$index$_name"/>
        <NEXT_OUTPUT_STRING id="script_output_param$index$_unit"/>
        <NEXT_OUTPUT_STRING id="script_output_param$index$_enum_values"/>
        <NEXT_OUTPUT_STRING id="script_output_param$index$_value_format"/>
    </REPEAT>
    <REPEAT count="$SCRIPT_STRINGS_COUNT$">
        <NEXT_OUTPUT_STRING id="script_input_string$index$_name"/>
    </REPEAT>
	<REPEAT count="$SCRIPT_OUT_STRINGS_COUNT$">
        <NEXT_OUTPUT_STRING id="script_output_string$index$_name"/>
    </REPEAT>
	 <REPEAT count="$SCRIPT_OUT_STRINGS_COUNT$">
        <NEXT_OUTPUT_STRING id="script_output_string$index$"/>
   </REPEAT>
    <!-- Extra params and variables *********************************************-->
    <!-- Opacity -->
    <PARAM id="global_opacity" min="0" max="100" default="100" unit="%" persistent="true"/>
    <PARAM_LINK from="global_opacity" to="window.opacity" normalized="true"/>

    <!-- Main audio bus channels-->
    <FORMULA_PARAM id="main_bus_channels_count" formula="min(dsp.connected_inputs_count,dsp.connected_outputs_count)"/>

    <!-- Custom parameters, built from param details in current script -->
    <REPEAT count="$SCRIPT_PARAMS_COUNT$">
        <!-- Input param for display and control, linked to actual DSP param-->
        <PARAM id="custom_param$index$" min="0" max="1" default="0" name="Param $index$"/>
        <PARAM_LINK from="$script_input_param$index$_min$" to="custom_param$index$.min"/>
        <PARAM_LINK from="$script_input_param$index$_max$" to="custom_param$index$.max"/>
        <PARAM_LINK from="$script_input_param$index$_default$" to="custom_param$index$.default"/>
        <STRING_LINK from="$script_input_param$index$_unit$" to="custom_param$index$.unit"/>
        <STRING_LINK from="$script_input_param$index$_name$" to="custom_param$index$.name"/>
        <STRING_LINK from="$script_input_param$index$_value_format$" to="custom_param$index$.value_format"/>
        <STRING_LINK from="$script_input_param$index$_enum_values$" to="custom_param$index$.enum_values"/>

        <PARAM_LINK from="$script_input$index$$" to="custom_param$index$" normalized="true" enabled="true" capture_enabled="false"/>
        <PARAM_LINK from="custom_param$index$" to="$script_input$index$$" enabled="false" id="link$index$" normalized="true"/>
        <PARAM_LINK from="custom_param$index$.capturing" to="link$index$.enabled"/>
    </REPEAT>
    <REPEAT count="$SCRIPT_OUT_PARAMS_COUNT$">
        <!-- Output param for display, linked to actual DSP param-->
        <PARAM id="custom_out_param$index$" min="0" max="1" default="0" name="Out Param $index$"/>
        <PARAM_LINK from="$script_output_param$index$_min$" to="custom_out_param$index$.min"/>
        <PARAM_LINK from="$script_output_param$index$_max$" to="custom_out_param$index$.max"/>
        <PARAM_LINK from="$script_output_param$index$_default$" to="custom_out_param$index$.default"/>
        <STRING_LINK from="$script_output_param$index$_unit$" to="custom_out_param$index$.unit"/>
        <STRING_LINK from="$script_output_param$index$_name$" to="custom_out_param$index$.name"/>
        <STRING_LINK from="$script_output_param$index$_value_format$" to="custom_out_param$index$.value_format"/>
        <STRING_LINK from="$script_output_param$index$_enum_values$" to="custom_out_param$index$.enum_values"/>
        <PARAM_LINK from="$script_output$index$$" to="custom_out_param$index$" normalized="true"/>
    </REPEAT>

    <!-- Custom actions-->
    <INCLUDE_ONCE file="$_SYSTEM_TYPE_$.inc"/>
    <STRING id="PlugNScript.script_name" default="No Script"/>
    <ACTION id="PlugNScript.ShowScriptsMenu" type="DisplayPlugNScriptMenu" script_file_name_string_id="PlugNScript.script_name"/>
    <ACTION id="OpenScriptDoc" type="OpenUrl" url_string_id="$script_doc_path$"/>
    <IF_EDITABLE>
      <ACTION id="OpenScriptFile" type="OpenUrl" url_string_id="$script_file_path$" application_string_id="global.edit_script_application"/>
      <ACTION id="OpenKUIMLFile" type="OpenUrl" url_string_id="$script_gui_path$" application_string_id="global.edit_kuiml_application"/>
      <ACTION id="OpenLogFile" type="OpenUrl" url_string_id="$log_file_path$"  application_string_id="global.open_log_application"/>
      <ACTION id="OpenScriptDirectory" type="OpenUrl" url_string_id="$script_file_path$" application="$FILE_EXPLORER_APP$"/>
    </IF_EDITABLE>
  
    <IF_NOT_EDITABLE>
      <ACTION id="OpenLogFile" type="OpenUrl" url_string_id="$log_file_path$" />
    </IF_NOT_EDITABLE>

  <!-- Editable checks-->
  <IF_EDITABLE>
    <VARIABLE id="is_editable" value="true"/>
    <VARIABLE id="is_not_editable" value="false"/>
  </IF_EDITABLE>
  <IF_NOT_EDITABLE>
    <VARIABLE id="is_editable" value="false"/>
    <VARIABLE id="is_not_editable" value="true"/>
  </IF_NOT_EDITABLE>

  <!-- editable mode: make sure DSP data is not stripped (not exposing all to improve performance)-->
  <IF_EDITABLE>
    <REPEAT count="$SCRIPT_PARAMS_COUNT$">
      <REQUIRED_OBJECTS object_ids="custom_param$index$.value_changed"/>
    </REPEAT>
    <REPEAT count="$SCRIPT_OUT_PARAMS_COUNT$">
      <REQUIRED_OBJECTS object_ids="custom_out_param$index$.value_changed"/>
    </REPEAT>
    <REPEAT count="$PLUGIN_INPUT_PARAMS_COUNT$">
      <REQUIRED_OBJECTS object_ids="dsp.input$index$;dsp.input$index$.value_changed;Show_dsp.input$index$_ControlSetup"/>
    </REPEAT>
    <REPEAT count="$PLUGIN_INPUT_STRINGS_COUNT$">
      <REQUIRED_OBJECTS object_ids="dsp.input_string$index$;dsp.input_string$index$.value_changed"/>
    </REPEAT>
    <REPEAT count="$PLUGIN_OUTPUT_PARAMS_COUNT$">
      <REQUIRED_OBJECTS object_ids="dsp.output$index$;dsp.output$index$.value_changed;Show_dsp.output$index$_ControlSetup"/>
    </REPEAT>
    <REPEAT count="$PLUGIN_PRIVATE_OUTPUT_PARAMS_COUNT$">
      <REQUIRED_OBJECTS object_ids="dsp.private_output$index$;dsp.private_output$index$.value_changed"/>
    </REPEAT>
    <REPEAT count="$PLUGIN_OUTPUT_STRINGS_COUNT$">
      <REQUIRED_OBJECTS object_ids="dsp.output_string$index$;dsp.output_string$index$.value_changed"/>
    </REPEAT>
  </IF_EDITABLE>
</DUMMY>