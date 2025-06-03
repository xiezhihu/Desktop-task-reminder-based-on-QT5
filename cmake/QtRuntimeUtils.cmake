function(configure_qt_runtime TARGET_NAME)
    if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(DEBUG_SUFFIX "")
        if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
            set(DEBUG_SUFFIX "d")
        endif ()

        set(QT_INSTALL_PATH "D:/Qt/5.15.2/msvc2019_64")

        # 尝试修正 bin 路径
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()

        # ================== 核心 DLL ====================
        set(QT_DLLS
                Core
                Gui
                Widgets
                Multimedia
                MultimediaWidgets
                Network
                Sql
                Xml
        )
        foreach (LIB ${QT_DLLS})
            set(DLL_FILE "${QT_INSTALL_PATH}/bin/Qt5${LIB}${DEBUG_SUFFIX}.dll")
            if (EXISTS "${DLL_FILE}")
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy "${DLL_FILE}"
                        "$<TARGET_FILE_DIR:${TARGET_NAME}>")
            endif ()
        endforeach ()

        # ================= 插件目录支持函数 ==================
        function(copy_qt_plugin plugin_type plugin_name)
            set(SRC "${QT_INSTALL_PATH}/plugins/${plugin_type}/${plugin_name}${DEBUG_SUFFIX}.dll")
            set(DST "$<TARGET_FILE_DIR:${TARGET_NAME}>/plugins/${plugin_type}/${plugin_name}${DEBUG_SUFFIX}.dll")
            if (EXISTS "${SRC}")
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        "$<TARGET_FILE_DIR:${TARGET_NAME}>/plugins/${plugin_type}")
                add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy "${SRC}" "${DST}")
            endif ()
        endfunction()

        # 平台插件
        copy_qt_plugin("platforms" "qwindows")

        # 多媒体插件
        copy_qt_plugin("mediaservice" "dsengine")

        # 音频插件（可选）
        file(GLOB AUDIO_PLUGINS "${QT_INSTALL_PATH}/plugins/audio/*${DEBUG_SUFFIX}.dll")
        foreach (PLUGIN ${AUDIO_PLUGINS})
            get_filename_component(PLUGIN_NAME "${PLUGIN}" NAME)
            copy_qt_plugin("audio" "${PLUGIN_NAME}")
        endforeach ()

        # 图像格式插件（支持 PNG/JPG/GIF 等）
        file(GLOB IMAGE_PLUGINS "${QT_INSTALL_PATH}/plugins/imageformats/*${DEBUG_SUFFIX}.dll")
        foreach (PLUGIN ${IMAGE_PLUGINS})
            get_filename_component(PLUGIN_NAME "${PLUGIN}" NAME_WE)
            copy_qt_plugin("imageformats" "${PLUGIN_NAME}")
        endforeach ()

        # 可扩展更多插件类型
        # copy_qt_plugin("iconengines" "qsvgicon")
        # copy_qt_plugin("sqldrivers" "qsqlite")
        # copy_qt_plugin("printsupport" "windowsprintersupport")
    endif ()
endfunction()
