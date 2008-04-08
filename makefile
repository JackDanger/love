default: prep love love_chipmunk love_opengl love_physfs love_sdlkeyboard love_sdlmixer love_sdlmouse love_sdltimer love_system

%:
	@if [ '$@' != 'default' ] && [ '$@' != 'clean' ]; then \
		echo; \
		echo Making $@ ...; \
		make -sf $@.make; \
	fi

clean-%: %.make
	@if [ '%' != 'clean' ]; then \
		echo Cleaning up temporary $< objects ...; \
		make -sf $< clean; \
	fi

prep:
	@mkdir obj &> /dev/null

clean: clean-love clean-love_chipmunk clean-love_opengl clean-love_physfs clean-love_sdlkeyboard clean-love_sdlmixer clean-love_sdlmouse clean-love_sdltimer clean-love_system
