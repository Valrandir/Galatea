.PHONY: clean All

All:
	@echo ----------Building project:[ CoreSpecimen - Debug ]----------
	@cd "CoreSpecimen" && "$(MAKE)" -f "CoreSpecimen.mk"
clean:
	@echo ----------Cleaning project:[ CoreSpecimen - Debug ]----------
	@cd "CoreSpecimen" && "$(MAKE)" -f "CoreSpecimen.mk" clean
