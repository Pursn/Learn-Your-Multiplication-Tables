MAIN_FILE = /usr/local/bin/lymt
CONF_FILE = $(HOME)/.lymt_conf
SHELL_TYPE := $(shell basename "$$SHELL")

install:
	#Remember that "-lm" links the math library to "main.c"
	sudo gcc main.c -o $(MAIN_FILE) -lm
	sudo chmod +x $(MAIN_FILE)

ifeq ($(SHELL_TYPE), bash)
	$(echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bashrc)
else ifeq ($(SHELL_TYPE), zsh)
	$(echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.zshrc)
endif

clean:
	sudo rm -rf $(MAIN_FILE)
	rm -rf $(CONF_FILE)
