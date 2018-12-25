// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <parquet/arrow/reader.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>
#include "arrow_types.h"
#include "table.h"

using namespace Rcpp;
using namespace arrow;

// [[Rcpp::export]]
List read_parquet_file(String path_) {
  // TODO: expand path
  std::string path(path_);

  // original code: https://github.com/apache/arrow/blob/0729cb771bd51f60423b52d44a50bddc45653d90/cpp/examples/parquet/parquet-arrow/src/reader-writer.cc#L64-L72
  std::shared_ptr<arrow::io::ReadableFile> infile;
  PARQUET_THROW_NOT_OK(arrow::io::ReadableFile::Open(
      path, arrow::default_memory_pool(), &infile));

  std::unique_ptr<parquet::arrow::FileReader> reader;
  PARQUET_THROW_NOT_OK(
    parquet::arrow::OpenFile(infile, arrow::default_memory_pool(), &reader));
  std::shared_ptr<arrow::Table> table;

  PARQUET_THROW_NOT_OK(reader->ReadTable(&table));

  return Table__to_dataframe(table);
}
