# Nebula Example

# 3.7.2 required for using FindVulkan
cmake_minimum_required(VERSION 3.7.2)

get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include(${FIPS_ROOT_DIR}/cmake/fips.cmake)

fips_setup(PROJECT modebrods-imba-project)
fips_include_directories(.)

nebula_begin_app(nebula-example windowed)
    
    fips_dir(code)
        fips_files(
            main.cc
            exampleapp.cc
            exampleapp.h
			entitymanager.cc
			entitymanager.h
			componentmanager.cc
			componentmanager.h
			entity.h
			componentinterface.cc
			componentinterface.h
			component.h
			componenttransform.cc
			componentgraphic.cc
			messagemanager.cc
			messagemanager.h
			message.h
        )

    fips_deps(foundation render resource dynui scripting)
nebula_end_app()

fips_finish()
