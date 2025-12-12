USE [SatelliteDB]
GO

/****** Object:  StoredProcedure [dbo].[GetSatellites]    Script Date: 12/12/2025 7:38:30 AM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO


CREATE PROCEDURE [dbo].[GetSatellites]
    @Name NVARCHAR(MAX) = NULL,
    @Class NVARCHAR(MAX) = NULL,
    @LaunchDate DATE = NULL,
    @Payload NVARCHAR(MAX) = NULL,
    @Agency NVARCHAR(MAX) = NULL,
    @IDN NVARCHAR(MAX) = NULL,
    @Status NVARCHAR(MAX) = NULL,
    @SortColumn NVARCHAR(50) = NULL,   -- optional
    @SortOrder NVARCHAR(4) = NULL      -- optional

/*
    DECLARE  @Name NVARCHAR(MAX) = NULL,
    @Class NVARCHAR(MAX) = NULL,
    @LaunchDate DATE = NULL,
    @Payload NVARCHAR(MAX) = NULL,
    @Agency NVARCHAR(MAX) = NULL,
    @IDN NVARCHAR(MAX) = NULL,
    @Status NVARCHAR(MAX) = NULL,
    @SortColumn NVARCHAR(50) = NULL,   -- optional
    @SortOrder NVARCHAR(4) = NULL  

   
    SET @Name = ''
    SET @Class = ''
    SET @LaunchDate = ''   -- accept as string
    SET @Payload = ''
    SET @Agency = ''
    SET @IDN = ''
    SET @Status= ''
    SET @SortColumn= 'Name'
    SET @SortOrder = 'ASC'
--*/ AS
BEGIN
    SET NOCOUNT ON;

    DECLARE @SQL NVARCHAR(MAX);

    -- Normalize empty strings to NULL
    SET @Name       = NULLIF(@Name,'');
    SET @Class      = NULLIF(@Class,'');
    SET @LaunchDate = NULLIF(CONVERT(NVARCHAR(20),@LaunchDate),'');
    SET @Payload    = NULLIF(@Payload,'');
    SET @Agency     = NULLIF(@Agency,'');
    SET @IDN        = NULLIF(@IDN,'');
    SET @Status     = NULLIF(@Status,'');

    -- Default sorting
    IF @SortColumn IS NULL OR @SortColumn NOT IN ('SatID','Name','Class','LaunchDate','Payload','Agency','IDN','Status')
        SET @SortColumn = 'SatID';

    IF @SortOrder IS NULL OR UPPER(@SortOrder) NOT IN ('ASC','DESC')
        SET @SortOrder = 'ASC';

    -- Base query
    SET @SQL = '
        SELECT SatID, Name, Class, LaunchDate, Payload, Agency, IDN, Status
        FROM Satellites
        WHERE ( @LaunchDate = ''1900-01-01'' OR LaunchDate = @LaunchDate )';

    -- Filters
    IF @Name IS NOT NULL
        SET @SQL += '
          AND Name IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Name, '',''))';

    IF @Class IS NOT NULL
        SET @SQL += '
          AND Class IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Class, '',''))';

    IF @Payload IS NOT NULL
        SET @SQL += '
          AND Payload IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Payload, '',''))';

    IF @Agency IS NOT NULL
        SET @SQL += '
          AND Agency IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Agency, '',''))';

    IF @IDN IS NOT NULL
        SET @SQL += '
          AND IDN IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@IDN, '',''))';

    IF @Status IS NOT NULL
        SET @SQL += '
          AND Status IN (SELECT LTRIM(RTRIM(value)) FROM STRING_SPLIT(@Status, '',''))';

    -- Sorting
    SET @SQL += ' ORDER BY ' + QUOTENAME(@SortColumn) + ' ' + @SortOrder;

    EXEC sp_executesql @SQL,
        N'@Name NVARCHAR(MAX), @Class NVARCHAR(MAX), @LaunchDate DATE, @Payload NVARCHAR(MAX), @Agency NVARCHAR(MAX), @IDN NVARCHAR(MAX), @Status NVARCHAR(MAX)',
        @Name, @Class, @LaunchDate, @Payload, @Agency, @IDN, @Status;
END;

GO


