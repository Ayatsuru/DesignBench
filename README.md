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

### Runtime Entity Catalog

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

A dedicated `DesignBenchEditor` module also provides project-level validators for:

- `DA_Entity_*`naming conventions
- Entity Definition asset location conventions

This allows invalid designer-authored data to be detected directly inside Unreal Editor.

### Entity Database Editor Tool

An Editor-only EntityDefinitions database is cached and exploited by a designer-facing Editor Utility Widget for a complete audit of EntityDefinitions.

- Editor-only `UEntityDatabaseEditorSubsystem`
- Dynamic EntityDefinition discovery and refresh
- Name and Gameplay Tag filtering
- Direct asset opening and Content Browser navigation
- Per-entity validation feedback
- Visible-row Valid / Warning / Invalid summary
- Full-project EntityDefinition audit through the Asset Registry and Editor Validator Subsystem

The runtime module never depends on this module.

## Architecture

Current architecture looks as follow:

- `DesignBench` — Runtime module
  - Entity definitions
  - Runtime catalog and queries

- `DesignBenchEditor` — Editor-only module
  - Entity Database tooling
  - Project-specific validators
  - Asset Registry based audits
  - Editor Utility Widget support

## SideNotes

The Asset Manager is used for the official EntityDefinition catalog,
while the Asset Registry is used by the validation audit so that
misplaced EntityDefinition assets can still be discovered and reported.