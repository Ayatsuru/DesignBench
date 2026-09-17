# DesignBench

**DesignBench** is an Unreal Engine Technical Design sandbox focused on designer-facing workflows, data-driven gameplay architecture, validation, debugging, and rapid iteration.

The project explores how C++ foundations can expose safe, flexible, and efficient workflows to Game Designers through Blueprint and editor tooling.

## Goals

DesignBench is primarily a learning and portfolio project built around Technical Design practices.

Its main goals are to explore:

- Data-driven gameplay architecture
- Designer-facing APIs and tools
- Safe data authoring and validation
- Fast gameplay iteration workflows
- Runtime debugging and observability
- Clear boundaries between C++ foundations and Blueprint workflows

## Current Features

### Entity Definitions

Gameplay entities are represented through `UPrimaryDataAsset`-based definitions containing:

- Display name
- Description
- Gameplay Tags
- Soft Actor Class reference

New entity definitions can be added without modifying the systems consuming them.

### Entity Catalog

A `UGameInstanceSubsystem` discovers and caches all available Entity Definitions through Unreal Engine's Asset Manager.

The catalog currently supports:

- Retrieving all available entities
- Blueprint-facing access to the catalog
- Filtering through `FGameplayTagQuery`
- Display-name text search

Blueprint consumers do not need to know how the Asset Manager or Primary Asset system works internally.

### Data Validation

Entity Definitions implement Unreal Engine's Data Validation system.

Current validation rules include:

- Display Name is required
- Actor Class is required
- At least one Gameplay Tag is required
- At least one `Entity.Type.*` tag is required
- Missing Description produces a warning

This allows invalid designer-authored data to be detected directly inside Unreal Editor.

## Architecture

Current architecture looks as follow:

Primary Data Assets -> Asset Manager -> EntityCatalogSubsystem -> Blueprint-facing API -> Designer Tools